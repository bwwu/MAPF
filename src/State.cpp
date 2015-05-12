#include "State.h"

#include <iostream>
using namespace std;

bool* Grid::adj(const Point& pos) const {
	int x = pos.x;
	int y = pos.y;
	if ( x < 0 || x >= dimX || y < 0 || y > dimY)
		return NULL;

	bool* adj = new bool[DIM];

	adj[NORTH] = y <= dimY-1 && grid[x][y+1];
	adj[EAST] = x <= dimX-1 && grid[x+1][y];
	adj[SOUTH] = y > 1 && grid[x][y-1];
	adj[WEST] = x > 1 && grid[x-1][y];


	for (int i=0;i<DIM;i++) 
		cout << ((adj[i]) ? 1:0);
	cout << endl;

	return adj;
}
		


Grid::Grid(int x, int y, Point** blocklist, int listlen): dimX(x),dimY(y) {
	Point** end	= blocklist + listlen;
	grid = new bool*[dimX];

	for (int i=0; i<dimX; i++) {
		grid[i] = new bool[dimY];

		for (int j=0; j<dimY; j++) {
			if (blocklist && pointEquals(*blocklist, i, j))
				blocklist = (blocklist+1==end) ? 0 : blocklist + 1;
			else
				grid[i][j] = true;
		}
	}

}

Grid::~Grid() {
	for (int i=0; i<dimX; i++) {
		delete [] grid[i];
	}
	delete [] grid;
}

void Grid::display(void) {
	for (int j=dimY-1;j>=0;j--) {
		for (int i=0;i<dimX;i++)
			cout << ((grid[i][j]) ? 1 : 0);
		cout << endl;
	}
}

int main() {

	Point* arr[5];
	
	arr[0] = new Point(1,2);
	arr[1] = new Point(1,3);
	arr[2] = new Point(2,3);
	arr[3] = new Point(2,4);
	arr[4] = new Point(4,4);

	Grid g(5,5, arr, 5);
	g.display();

	bool* a = g.adj(Point(2,2));
	a = g.adj(Point(2,4));
	return 0;

}
