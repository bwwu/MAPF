#include "State.h"

#include <iostream>
using namespace std;

void State::display(void) {
	for (int i=0; i<n; i++) {
		cout << "(" << pre_move[i].x << "," << pre_move[i].y << ") ";
		cout << "(" << post_move[i].x << "," << post_move[i].y << ")";
		cout << endl;
	}
}


State::State(int n, const State& parent, const Move& move): n(n)
{ 
	this->parent = &parent;
	int pid = move.p;

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
}

// Specify initial state
State::State(Point* init, int n): n(n) {
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


