#include "Search.h"
#include <limits>
#include <list>
#include <vector>
#include <iostream>
using namespace std;

Search::Search(int n, Point* init, Point* goal, Grid* g):
	n(n), goal(goal), grid(g) {
	
	/*	Add initial state to open list */
	Node* tmp = new Node;
	tmp->p = NULL;
	tmp->s = new State(init, n);
	tmp-> f = tmp->s->h(goal);
	tmp->turn = 0;
	open.push_back(tmp);
}

Search::~Search() {}

bool Search::expand(void) {
	//cout << "Expanding\n========\n";
	/* Choose node on open with min f cost */
	int min = std::numeric_limits<int>::max();
	Node* nd = NULL;		//Node to expand

	auto it = open.begin();
	auto del = open.begin();

	for (it; it < open.end(); it++) {
		if((*it)->f <= min) {
			min = (*it)->f;
			del = it;
			nd = *it;
		}
	}

	if (!nd) { 
		cout << "ERROR: NULL chosen for expansion\n";
		return false;
	}
	open.erase(del);	// Remove from open list

	/* Check if node chosen for exp is goal */
	if (is_goal(nd))
		return true;

	/* Get adj list for position of agent about to move */
	int turn = nd->turn;
//	Point* pt = nd->s->get_pos(turn);
//	bool* adjm = (pt) ? grid->adj(*pt) : NULL;
//
//	if (!adjm) {
//		cout << "ERROR\n";
//		return false;
//	}	
//	for (int i=0; i<DIM; i++) 
//		if (adjm[i]) {
//			open.push_back(generate(nd, i));
//		}
//	open.push_back(generate(nd, WAIT));
//
//	delete [] adjm;
	bool* valid_m = nd->s->valid_moves(turn, grid);
	for (int i=0; i<DIM+1;i++) {
		if (valid_m[i]) 
			open.push_back(generate(nd,i));
	}

	delete [] valid_m;
	return false;
}

Node* Search::generate(Node* p, int dir) {
	Node* child = new Node;
	Move m((Card)dir, p->turn);

	child->p = p;
	child->turn = (p->turn+1 == n) ? 0 : p->turn+1;
	child->s = new State(n, *(p->s), m);
	child->f = p->s->g() + child->s->h(goal);
	child->dir = dir;

	/****Debug****
	cout << "Generating move for Agent: " + (p->turn) <<
		" In direction: " << dir << "\n\tFrom: ";
	child->p->s->display();
	cout << "\tTo: ";
	child->s->display();
	cout << "\t h(n) = " << child->f << endl;
	**** Debug ****/

	return child;
}

/* Return true if node is a goal node */
bool Search::is_goal(Node* nd) {
	for (int i=0; i<n; i++) {
		Point* p = nd->s->get_pos(i);
		if (goal[i].x != p->x || goal[i].y != p->y)
			return false;
	}
	cout << "Found goal with cost " << nd->s->g() << "!\n";
	backtrace(nd);
	return true;
}

void Search::backtrace(Node* walk) {
	if (!walk) return;

	
	do {
		cout << "\nMove " << walk->dir << endl;
		cout << "Agent " << walk->p->turn << endl;
		walk = walk->p;
	} while (walk->p); 

//	vector<int> moves;
//		
//	do {
//		moves.push_back(walk->dir);	// dir that the parent
//		walk = walk->p;
//	} while (walk->p);
//
//
//	for (int i=0; i<n; i++) {
//		cout << "Player " << i << " moves\n";
//		for (int j = (moves.size()/n); j>=0; j--) {
//			int it = moves[j*n+i];
//		//auto it = moves[i].begin();
//		//for (it; it != moves[0].end(); it++)
//			switch((Card) it ) {
//			case NORTH:
//				cout << "North\n";
//				break;
//			case SOUTH:
//				cout << "South\n";
//				break;
//			case EAST:
//				cout << "East\n";
//				break;
//			case WEST:
//				cout << "West\n";
//			case WAIT:
//				cout << "Wait\n";
//			}
//		}
//	}
//
	
}


