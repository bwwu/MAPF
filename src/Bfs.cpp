/* Written by Brandon Wu */
#include "Bfs.h"
#include "Globals.h"
#include <limits>
#include <queue>
#include <iostream>
using namespace std;

//int reverse(int dir);	// Reverse a direction
void printpoint(Point p) {
	cout << "(" << p.x << "," << p.y << ")\n";
}

void Bfs::search(void) {
	queue<GNode> openlist;
	openlist.push(GNode(*orig, WAIT,0));

	int itcount = 0;	// Iteration count

	while (!openlist.empty()) { // && itcount < DLIM) {
		GNode sel = openlist.front();
		openlist.pop();

		if (sel.p.x == dest->x && sel.p.y == dest->y) {
			solncost = sel.depth;
			return;
		}
		/*cout << "PARENT: ";
		printpoint(sel.p);*/

		bool* adjlist = grid->adj(sel.p);
 		for (int i=0; i<DIM; i++) {
			/* If dir i is adjacent and is not reverse 
			 * dir from parent */
			if (adjlist && i!=sel.dir &&  adjlist[i])  {
			//if (adjlist &&  adjlist[i])  {
				Point child = move_dir(&(sel.p), i);
				int parentdir = reverse(i);
				int depth = sel.depth+1;
				/*cout << "\t" + dir2str(i);
				printpoint(child);*/
				int hash = child.x*dim.y + child.y;
				if (!visited[hash]) {
					openlist.push(GNode(child,parentdir,depth));
					visited[hash] = true;
				}
			}
		}
		delete [] adjlist;
		itcount++;
	}
}

Bfs::Bfs(Point* o, Point* d, Grid* g): orig(o), dest(d), grid(g) {
	solncost = numeric_limits<int>::max();

	dim = g->dim();
	len = dim.x*dim.y;
	visited = new bool[len]();
	
	search();
}
