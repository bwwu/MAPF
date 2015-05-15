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

Search::~Search() {}

void
Search::expand(void) {
	cout << "Expanding\n========\n";
	/* Choose node on open with min f cost */
	int min = std::numeric_limits<int>::max();
	Node* n = NULL;		//Node to expand

	auto it = open.begin();

	for (it; it < open.end(); it++) {
		if((*it)->f <= min) {
			min = (*it)->f;
			n = *it;
		}
	}

	if (!n) { 
		cout << "ERROR: NULL chosen for expansion\n";
		return;
	}

	/* Get adj list for position of agent about to move */
	//cout << "Expanding: " << n->
	int turn = n->turn;
	bool* adjm = grid->adj(*(n->s->get_pos(turn)));

	for (int i=0; i<DIM; i++) {
		if (adjm[i]) {
			open.push_back(generate(n, i));
		}
	open.push_back(generate(n, WAIT));

	//open.erase(it);
	//delete [] adjm;

}

Node* Search::generate(Node* p, int dir) {
	Node* child = new Node;
	Move m((Card)dir, p->turn);

	child->p = p;
	child->turn = (p->turn+1 == n) ? 0 : p->turn+1;
	child->s = new State(n, *(p->s), m);
	child->f = p->s->g() + child->s->h(goal);

	/**** Debug ****/
	cout << "Generating move for Agent: " + (p->turn) <<
		" In direction: " << dir << "\n\tFrom: ";
	child->p->s->display();
	cout << "\tTo: ";
	child->s->display();
	cout << "\t h(n) = " << child->f << endl;
	/**** Debug ****/

	return child;
}

