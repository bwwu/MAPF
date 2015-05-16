#ifndef SEARCH_H
#define SEARCH_H

/* Implements A* exploration on a grid 
		Maintains open list of search nodes and a goal state*/



#include "State.h"

#include <vector>
#include <string>
using namespace std;

struct Node {
	int f;		// f(n) = g(n) + h(n)
	int turn;	// id of agent to move
	State* s;	
	//Node* c[DIM+1];
	Node *p;
};

class Search {
public:
	bool expand(void);	// Return TRUE if goal is expanded
	
	
	Search(int n, Point* init, Point* goal, Grid* g);
	~Search();


private:
	Node*	generate(Node* p, int dir);	// Generate child of node
	bool	is_goal(Node* nd);	// Return TRUE if nd is goal node

	int 	n;
	Grid* 	grid;
	Point* 	goal;

	vector<Node*> open;	//Open list
};

#endif //SEARCH_H
