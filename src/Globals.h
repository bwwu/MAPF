/* Written by Brandon Wu */
#ifndef GLOBALS_H
#define GLOBALS_H
#include "Grid.h"

struct Mapf_t{	// MAPF Test Node 
	int 	num_agents;	// # of agents in the puzzle
	int	num_exp;	// Total # of node expansions
	time_t	time;	// Total time taken
	bool 	solved;	// Whether MAPF could solve the puzzle
	Point	dim;	// Dimensions of the grid
	Mapf_t(int na, int ne, time_t t, bool s, Point d):
		num_agents(na), num_exp(ne), time(t), solved(s), dim(d) {}
};


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

Mapf_t run_mapf(string path_g, string path_a);

bool mapftest(string testfile);

inline
bool pointEquals(Point* p1, int i, int j) {
	return (p1->x == i && p1->y == j);
}

#endif //GLOBALS_H
