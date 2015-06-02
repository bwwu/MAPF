#ifndef DISTANCE_H
#define DISTANCE_H

#include "Bfs.h"
#include "Grid.h"
#include <unordered_map>
#include <climits>
#include <iostream>
using namespace std;

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
	int dimX;	
	int dimY;
	int** table;	// Lookup table for BFS heuristic
};

inline
int Distance::lookup(const Point& i, const Point& dest) {
	//cout << "Lookup " << i.x << "," << i.y;
	//cout << " " << dest.x << "," << dest.y << endl;
	return table[i.x*dimY+i.y][dest.x*dimY+dest.y];

}

#endif //DISTANCE_H
