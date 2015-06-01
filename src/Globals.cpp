/* Written by Brandon Wu */
#include "Globals.h"
#include "Grid.h"

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


