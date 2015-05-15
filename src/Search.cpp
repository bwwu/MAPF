#include <limits>
#include <iostream>
using namespace std;
#include "Search.h"



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

void
Search::expand(void) {
	/* Choose node on open with min f cost */
	int min = std::numeric_limits<int>::max();
	Node* n = NULL;		//Node to expand

	for (auto it = open.begin(); it < open.end(); it++) {
		if((*it)->f < min) {
			min = (*it)->f;
			n = *it;
		}
	}

	if (!n) { 
		cout << "ERROR: NULL chosen for expansion\n";
		return;
	}
	

	
	
}
