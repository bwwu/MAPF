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
	State(Point* init, int n);
	State(int n, const State& parent, const Move& move);
	~State();
private:
	int 	n;
	const	State* parent;
	Point*	pre_move;
	Point*	post_move;
};

#endif //STATE_H
