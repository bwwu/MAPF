/* Written by Brandon Wu */

#ifndef BFS_H
#define BFS_H

#include "Grid.h"
#define DLIM 1000000	// Limit search depth

struct GNode {
	Point p;	// This point
	int dir;	// Direction to parent
	int depth;
	GNode(Point c, int dir, int depth): p(c), dir(dir), depth(depth) { };
};

class Bfs {
	public:
		Bfs(Point* o, Point* d, Grid* g);
		int cost(void);
		
	private:
		void search();
		int solncost;	// Soln cost
		Grid* grid;
		Point* orig;	// Origin point
		Point* dest;	// Dest point	
};

inline
int Bfs::cost(void) { return solncost; }
	
int reverse(int dir);	// Return the reverse direction	
#endif //BFS_H
