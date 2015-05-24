/* Written by Brandon Wu */

#include "Bfs.h"
#include <limits>
#include <queue>
using namespace std;

//int reverse(int dir);	// Reverse a direction

void Bfs::search(void) {
	queue<GNode> openlist;
	openlist.push(GNode(*orig, WAIT,0));

	int itcount = 0;	// Iteration count

	while (!openlist.empty() && itcount < DLIM) {
		GNode sel = openlist.front();
		openlist.pop();

		if (sel.p.x == dest->x && sel.p.y == dest->y) {
			solncost = sel.depth;
			return;
		}

		bool* adjlist = grid->adj(sel.p);
 		for (int i=0; i<DIM; i++) {
			/* If dir i is adjacent and is not reverse 
			 * dir from parent */
			if (adjlist && i!=sel.dir &&  adjlist[i])  {
				Point child = move_dir(&(sel.p), i);
				int parentdir = reverse(i);
				int depth = sel.depth+1;

				openlist.push(GNode(child,parentdir,depth));
			}
		}
		delete [] adjlist;
		itcount++;
	}
}

Bfs::Bfs(Point* o, Point* d, Grid* g): orig(o), dest(d), grid(g) {
	solncost = numeric_limits<int>::max();
	search();
}


int reverse(int dir) {
	switch(dir) {
	case NORTH:
		return SOUTH;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	case EAST:
		return WEST;
	default:
		return dir;
	}
}
