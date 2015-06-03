#ifndef DISTANCE_H
#define DISTANCE_H

#include "Bfs.h"
#include "Grid.h"
#include <unordered_map>

struct Key {
	Point init;	// Initial state
	Point goal;	// Goal state
	Key(Point i, Point g): init(i), goal(g) {};
};

class Distance {
public:
	int lookup(const Point& i, const Point& g);
	Distance(Grid* g);
	~Distance();

private:
	void populate(void);
	void search(Point& o, Point& d);
	Grid* g;
	int** table;	// Lookup table for BFS heuristic
};

inline
int Distance::lookup(const Point& i, const Point& g) {
	Point dim = this->g->dim();
	int dimX = dim.x;
	int dimY = dim.y;

	return table[i.x*dimY+i.y][g.x*dimY+g.y];

}

#endif //DISTANCE_H
