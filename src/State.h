#ifndef STATE_H
#define STATE_H

#define DIM 4

#include <string>

enum Card {	NORTH, SOUTH, EAST, WEST, WAIT};

struct Point {
	int x;
	int y;
	Point(int posx, int posy): x(posx), y(posy) {}
};

class Grid {
public:
	bool* adj(const Point& pos) const;
	void display(void);

	Grid(int dimX, int dimY, Point** blocklist, int listlen);
	~Grid();

private:
	bool**	grid;
	int	dimX;
	int	dimY;	
};


inline
bool pointEquals(Point* p1, int i, int j) {
	return (p1->x == i && p1->y == j);
}

#endif //STATE_H
