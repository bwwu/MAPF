/* Written by Brandon Wu */
#include "Globals.h"
#include "Grid.h"
#include "test.h"
/* TODO: Move chksolution out of test.cpp and into globals */

#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>

bool valid_pt(Point* p, const Grid& g) {
	return g.adj(*p);
}

/* Move point from in direction dir and Return resulting point */
Point move_dir(Point* from, int dir) {
	Point p(from->x, from->y);
	switch(dir) {
	case NORTH:
		p.y++;
		return p;
	case SOUTH:
		p.y--;
		return p;
	case EAST:
		p.x++;
		return p;
	case WEST:
		p.x--;
		return p;
	case NE:
		p.y++;
		p.x++;
		return p;
	case NW:
		p.y++;
		p.x--;
		return p;
	case SE:
		p.y--;
		p.x++;
		return p;
	case SW:
		p.y--;
		p.x--;
	default:
		return p;
	}
}

/* Given direction return string representing the direction */
string dir2str(int dir) {
	switch(dir) {
	case NORTH:
		return "North";
	case SOUTH:
		return "South";
	case EAST:
		return "East";
	case WEST:
		return "West";
	case NE:
		return "Northeast";
	case NW:
		return "Northwest";
	case SE:
		return "Southeast";
	case SW:
		return "Southwest";
	case WAIT:
		return "Wait";
	default:
		return "";
	}
}

/* Return the reverse direction */
int reverse(int dir) {
	switch(dir) {
	case NORTH:
		return SOUTH;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	case EAST:
		return WEST;
	case NE:
		return SW;
	case NW:
		return SE;
	case SE:
		return NW;
	case SW:
		return NE;
	default:
		return dir;
	}
}

/* Get the resulting direction from moving from pt A to B */
int getdir(Point* a, Point* b) {
	int dx, dy, diff;
	if (!(a&&b)) return -1;	// Error
	dx = b->x - a->x;
	dy = b->y - a->y;
	diff = 4*dy + dx;
	switch (diff) {
	case 5:
		return NE;
	case 4:
		return NORTH;
	case 3:
		return NW;
	case 1:
		return EAST;
	case -1:
		return WEST;
	case -3:
		return SE;
	case -4:
		return SOUTH;
	case -5:
		return SW;
	default:
		return WAIT;
	}
}

Point** readpos_agent(string pathname, int& n) {
	/*	@pathname = pathname to file
		@n = set the number of agents
	*/
	ifstream file(pathname);

	if (file.is_open()) {
		int num_agents;
		Point** arr = new Point*[2];
		file >> num_agents;	// First line should contain the num of agents
		arr[0] = new Point[num_agents];	// Initial state
		arr[1] = new Point[num_agents];	// Goal states

		for (int i=0; i<num_agents; i++) {
			file >> arr[0][i].x;
			file >> arr[0][i].y;
			file >> arr[1][i].x;
			file >> arr[1][i].y;
		}
		n = num_agents;
		return arr;
	}
	else {
		cout << "Cannot open file " + pathname + "\n";
		return NULL;
	}
}

bool mapftest(string testfile) {
	string line;
	ifstream file(testfile);
	int pos = 0, total=0;	// Number of test instances

	vector<Mapf_t> mapf_tests;
	
	if(!file.is_open()) return false;
	
	while(getline(file,line)) {
		if (line[0] == '#') continue;	

		string grid_path = line;
		string agent_path;
		getline(file, agent_path);
		cout << "grid path= "+grid_path+"\t agent path= "+agent_path+"\n";

		Mapf_t tmp = run_mapf(grid_path, agent_path);
		mapf_tests.push_back(tmp);
		if (tmp.solved)
			pos++;

		else cout << "Cannot solve instance " << total << endl;

		total++;
	}

	file.close();
	cout << "Solved " << pos << "/" << total << " instances\n";

	return true;
}


Mapf_t run_mapf(string path_g, string path_a) {

	//string path_g(argv[1]);
	//string path_a(argv[2]);
	int num_agents = -1;

	Point** states = readpos_agent(path_a,num_agents);
	Grid grid("../grids/" + path_g);

	Mapf_t info(num_agents, 0, 0, false, grid.dim());

	if (!chksolution((int*)states[0], (int*)states[1], num_agents, &grid))
		return info;

	Mapf m(num_agents, states[0], states[1], &grid);


	while (m.resolve_conflicts());
	cout << "\tTotal Nodes Expanded: " << m.num_expansions() << endl;	
	cout << fixed;
	cout << "\tTotal Time " << setprecision(8) << m.get_time() << "s\n";

	info.solved = true;
	info.num_exp = m.num_expansions();

	delete [] states[0];
	delete [] states[1];
	delete [] states;

	return info;
}

