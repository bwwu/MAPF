/* Written by Brandon Wu */

#include "State.h"
#include "Bfs.h"
#include "Globals.h"

//#include "Search.h"

#include <limits>
#include <string>
#include <iostream>
using namespace std;

bool* State::valid_moves(int agent, Grid* grid) {
	Point* pt = get_pos(agent);
	if (!pt) return NULL;
	
	bool* vld = new bool[DIM+1];

	vld[WAIT] = (collision(pt, agent, true)) ? false : true;

	bool* adjm = grid->adj(*pt);
	if (!adjm) 
		return vld;

	for (int i=0; i<DIM; i++) {
		if (adjm[i]) {
			Point move = move_dir(pt, i);
			if (collision(&move, agent, true))
				vld[i] = false;
			else vld[i] = true;
		}
		else vld[i] = false;
	}
	delete [] adjm;

//	cout << "ADJ For Pt " << pt->x << "," << pt->y << endl;
//	for (int i=0; i<DIM+1;i++)
//		if (vld[i]) cout << "1";
//		else cout << "0";
//	cout << endl;

	return vld;
}


void State::display(void) {
	for (int i=0; i<n; i++) {
		cout << "Pre=(" << pre_move[i].x << "," << pre_move[i].y << ") ";
		cout << "Post=(" << post_move[i].x << "," << post_move[i].y << ")";
		cout << endl;
	}
}

Point* State::collision(Point* p, int agent, bool post) {
	// RETURN NULL if no collision. Otherwise RETURN ptr
	// to colliding agent
	//	@post - True if to compare with post_move positions
	Point* cmp = (post) ? post_move : pre_move;
	for (int i=0; i<n; i++) {
		if (i != agent && p->x == cmp[i].x && p->y == cmp[i].y)
			return &cmp[i];
		if (post && i == agent)	// Only search agents already placed
			return NULL;
	}
	return NULL;
}

/********* Constructors & Destructors *******/
State::State(int n, const State& parent, const Move& move): n(n) { 
	int pid = move.p;
	cost = parent.cost+1;

	if (pid)	// If agent id != 0
		this->parent = (&parent)->parent;
	else this->parent = &parent;

	pre_move = new Point[n];
	post_move = new Point[n];

	for (int i=0; i<n;i++) {
		pre_move[i] = parent.pre_move[i];
		post_move[i] = parent.post_move[i];
	}

	switch(move.dir) {
	case NORTH:
		post_move[pid].y++;
		break;
	case SOUTH:
		post_move[pid].y--;
		break;
	case EAST:
		post_move[pid].x++;
		break;
	case WEST:
		post_move[pid].x--;
		break;
	default:;
	}	
	if (pid == n-1)	
		increment_step();
}

// Specify initial state
State::State(Point* init, int n): n(n), cost(0) {
	pre_move = new Point[n];
	post_move = new Point[n];
	for (int i=0; i<n; i++) {
		pre_move[i] = init[i];
		post_move[i] = init[i];
	}
}

State::~State( ) {
	delete [] pre_move;
	delete [] post_move;
}

/* True distance heuristic */
int State::h(Point* goal, Grid* grid) {
	int dist = 0;
	int max_int = numeric_limits<int>::max();
	for (int i=0;i<n; i++) {
		Point p_init = post_move[i];
		Point p_goal = goal[i];
		Bfs bfs(&p_init, &p_goal, grid);
		if (bfs.cost() == max_int) 
			return max_int;
		dist += bfs.cost();
	}
	return dist;
}

