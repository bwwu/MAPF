#include "State.h"

#include <vector>
#include <string>
using namespace std;

struct Node {
	int f;		// f(n) = g(n) + h(n)
	int turn;	// id of agent to move
	State* s;	
	Node* c[DIM];
	Node *p;
};

class Search {
public:
	void expand(void);
	
	Search(int n, Point* init, Point* goal, Grid* g);
	~Search();


private:
	int 	n;
	Grid* 	grid;
	Point* 	goal;

	vector<Node*> open;	//Open list
};
