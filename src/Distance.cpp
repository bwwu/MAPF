#include "Distance.h"
#include <iostream>
using namespace std;

Distance::Distance(Grid* g): g(g) {
	Point dim = g->dim();
	table = new int*[dim.x*dim.y];
	for (int i=0; i<dim.x*dim.y; i++)
		table[i] = new int[dim.y*dim.x];

	populate();

}

void Distance::populate(void) {
	/* Populate the heuristic lookup table */
	Point dim = g->dim();
	int dimX = dim.x;
	int dimY = dim.y;
	for (int i=0; i<dimX; i++) {
		for (int j=0; j<dimY; j++) {
			Point orig(i,j);
			for (int k=0; k<dimX; k++) {
				for (int l=0; l<dimY; l++) {
					Point dest(k,l);
					search(orig, dest);
				}
			}
		}
	}
}

void Distance::search(Point& o, Point& d) {
	Point dim = g->dim();
	int dimX = dim.x;
	int dimY = dim.y;

	//cout << o.x << "," << o.y << " " << d.x << "," << d.y << endl;
	Bfs bfs(&o, &d, this->g);
	table[o.x*dimY+o.y][d.x*dimY+d.y] = bfs.cost();
}

Distance::~Distance() {
	Point dim = g->dim();
	int dimX = dim.x;
	int dimY = dim.y;

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
