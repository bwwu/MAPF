/* Written by Brandon Wu */
#ifndef GRID_H
#define GRID_H

#define DIM 4	//Change to 8 from 4

#include <string>
using namespace std;
enum Card {	NORTH, SOUTH, EAST, WEST, NE, NW, SE, SW, WAIT};

struct Point {
	int x;
	int y;
	Point(int posx, int posy): x(posx), y(posy) {}
	Point(): x(0),y(0) {};
};

class Grid {
public:
	bool*	adj(const Point& pos) const;
	int	hash_pt(Point* p);	
	void	display(void);

	Grid(int dimX, int dimY, Point** blocklist, int listlen);
	Grid(string pathname);
	~Grid();

private:
	bool**	grid;
	int	dimX;
	int	dimY;	
};

inline
int Grid::hash_pt(Point* p) {
	return (p->x)*dimY + p->y;
}
#endif //GRID_H
