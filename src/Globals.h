/* Written by Brandon Wu */
#ifndef GLOBALS_H
#define GLOBALS_H
#include "Grid.h"

/* Move point in a direction dir */
Point move_dir(Point* from, int dir);
/* Return string representation from direction enum */
string dir2str(int dir);
/* Return the reverse direction */
int reverse(int dir);
/* Find the direction resulting btw the 2 points */
int getdir(Point* a, Point* b);
/* Read an array of points as initial positions and final positions
	from a file */
Point** readpos_agent(string pathname, int& n);


inline
bool pointEquals(Point* p1, int i, int j) {
	return (p1->x == i && p1->y == j);
}
#endif //GLOBALS_H
