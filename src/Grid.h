/* Written by Brandon Wu */

#ifndef GRID_H
#define GRID_H

#define DIM 4

#include <string>
using namespace std;
enum Card {	NORTH, SOUTH, EAST, WEST, WAIT};

struct Point {
	int x;
	int y;
	Point(int posx, int posy): x(posx), y(posy) {}
	Point(): x(0),y(0) {};
};

class Grid {
public:
	bool* adj(const Point& pos) const;
	void display(void);

	Grid(int dimX, int dimY, Point** blocklist, int listlen);
	Grid(string pathname);
	~Grid();

private:
	bool**	grid;
	int	dimX;
	int	dimY;	
};

Point move_dir(Point* from, int dir);

inline
bool pointEquals(Point* p1, int i, int j) {
	return (p1->x == i && p1->y == j);
}

#endif //GRID_H
