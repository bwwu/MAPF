/* Written by Brandon Wu */

#ifndef STATE_H
#define STATE_H
/* Describes Search State
		For A* search with Operator Decomposition
		pre_move[n] and post_move[n] contains array of positions
		for n players */

#include "Grid.h"

#include <iostream>
using namespace std;

struct Move {
	Card	dir;
	int	p;
	Move(Card dir, int p):dir(dir),p(p) { };
};

class State {
public: 
	void display(void);	// Display pre-moves and post-moves for ea. agent
	int h(Point* goal);	// Manhattan Distance Heuristic
	int h(Point* goal, Grid* g);	// True Distance Heuristic

	int g(void);		// Cost from root
	bool*	valid_moves(int, Grid*);	// list of valid moves for agent n
	Point* get_pos(int id);	// Get pre-move pos of agent id

	/**** Constructors ****/
	State(Point* init, int n);
	State(int n, const State& parent, const Move& move);
	~State();
private:
	int 	n;
	int	cost;
	const	State* parent;
	Point*	pre_move;
	Point*	post_move;

	void increment_step();
	Point* collision(Point* p, int agent, bool post);
};

// Heuristic value -- Manhattan distance
inline
int State::h(Point* goal) {
	int cost = 0;
	for (int i=0; i<n; i++) {
		int xd = goal[i].x - post_move[i].x;
		int yd = goal[i].y - post_move[i].y;
		cost += (xd > 0) ? xd : -xd;
		cost += (yd > 0) ? yd : -yd;
	}
	return cost;
}

inline
int State::g(void) {
	return cost;
}

inline
Point* State::get_pos(int id) {
	return (id >= 0 && id < n) ? &pre_move[id] : NULL;
}

inline
void State::increment_step(void) {
	for (int i=0; i<n; i++)
		pre_move[i] = post_move[i];
}


#endif //STATE_H
