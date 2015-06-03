/* Written by Brandon Wu */
#ifndef SEARCH_H
#define SEARCH_H

/* Implements A* exploration on a grid 
		Maintains open list of search nodes and a goal state*/


#include "Grid.h"
#include "State.h"

#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Node {
	int f;		// f(n) = g(n) + h(n)
	int turn;	// id of agent to move
	int dir;	// direction from parent
	State* s;	
	Node *p;
	bool operator<(const Node& lhs) const { return lhs.f < f; };
};

struct Node_t {
	Node* n;
	Node_t(Node* ptr): n(ptr){};
	bool operator<(const Node_t& lhs) const { 
		return n->operator<(*(lhs.n)); 	}
};

class Search {
public:
	int	expand(void);	// Return 1 if goal is expanded
	int	num_expansions(void);	// Return num of node expansion
	vector<int>* path(bool print);	// Retrieve the path found from goal
	
	Search(int n, Point* init, Point* goal, Grid* g);
	~Search();

private:
	Node*	generate(Node* p, int dir);	// Generate child of node
	bool	is_goal(Node* nd);	// Return TRUE if nd is goal node
	vector<int>* backtrace(Node* w);	// Determine path from root to w
	
	int*	reconstruct_path(int agent, const vector<int>& tr);

	int 	n;
	int	exp_cnt;	// Number of node expansions
	Grid* 	grid;
	Point* 	goal;	// Set of goal states
	Point*	init;	// Set of initial states

	Node*	current;	// Set to goal node if found (TODO: make current)

	priority_queue<Node_t> open;	// Open list
	

};

inline
int Search::num_expansions(void) { return exp_cnt; }

#endif //SEARCH_H
