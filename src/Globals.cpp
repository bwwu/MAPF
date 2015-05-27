#include "Globals.h"
#include "Grid.h"

/* Move point from in direction dir and Return resulting point */
Point move_dir(Point* from, int dir) {
	Point p(from->x, from->y);
	switch(dir) {
	case NORTH:
		p.y++;
		break;
	case SOUTH:
		p.y--;
		break;
	case EAST:
		p.x++;
		break;
	case WEST:
		p.x--;
		break;
	default:;
	}
	return p;
}

/* Given direction return string representing the direction */
string dir2str(int dir) {
	switch(dir) {
	case NORTH:
		return "North";
	case SOUTH:
		return "South";
	case EAST:
		return "East";
	case WEST:
		return "West";
	case WAIT:
		return "Wait";
	default:
		return "";
	}
}

/* Return the reverse direction */
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

/* Get the resulting direction from moving from pt A to B */
int getdir(Point* a, Point* b) {
	int dx, dy, diff;
	if (!(a&&b)) return -1;	// Error
	dx = b->x - a->x;
	dy = b->y - a->y;
	diff = 4*dy + dx;
	switch (diff) {
	case 4:
		return NORTH;
	case 1:
		return EAST;
	case -1:
		return WEST;
	case -4:
		return SOUTH;
	default:
		return WAIT;
	}
}
