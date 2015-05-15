#ifndef STATE_H
#define STATE_H

#include "Grid.h"

struct Move {
	Card	dir;
	int	p;
	Move(Card dir, int p):dir(dir),p(p) { };
};

class State {
public: 
	void display(void);
	int h(Point* goal);	// Heuristic value to goal
	int g(void);	// Cost from root

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
void State::increment_step(void) {
	for (int i=0; i<n; i++)
		pre_move[i] = post_move[i];
	cost++;
}


#endif //STATE_H
