#include "Distance.h"
#include <iostream>
using namespace std;

Distance::Distance(Grid* g): g(g) {
	Point dim = g->dim();
	dimX = dim.x;
	dimY = dim.y;

	table = new int*[dimX*dimY];
	for (int i=0; i<dimX*dimY; i++)
		table[i] = new int[dimX*dimY];

	populate();

}

void Distance::populate(void) {
	/* Populate the heuristic lookup table */
	for (int i=0; i<dimX; i++) {
		for (int j=0; j<dimY; j++) {
			Point orig(i,j);
			for (int k=i; k<dimX; k++) {
				for (int l=j; l<dimY; l++) {
					Point dest(k,l);
					search(orig, dest);
				}
			}
		}
	}
}

void Distance::search(Point& o, Point& d) {
	//cout << o.x << "," << o.y << " " << d.x << "," << d.y << endl;
	Bfs bfs(&o, &d, this->g);
	table[o.x*dimY+o.y][d.x*dimY+d.y] = bfs.cost();
	table[d.x*dimY+d.y][o.x*dimY+o.y] = bfs.cost();
}

Distance::~Distance() {
	for (int i=0;i<dimX*dimY;i++)
		delete [] table[i];
	delete [] table;
}
/*
int main() {
	Grid g("../grids/t5_g3.txt");
	Distance d(&g);
	cout << "Done\n";
	while(true);
}*/
