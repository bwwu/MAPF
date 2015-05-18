#ifndef MAPF_H
#define MAPF_H

#include "Search.h"
#include "Grid.h"

struct agent_t {	// Agent type
	int id;
	Point init;
	Point goal;
	vector<int>* path;
	agent_t(int id, Point init, Point goal): id(id), init(init), goal(goal),
		path(NULL) {};
};

class Mapf {
public:
	Mapf(int n, Point* s_init, Point* s_goal, Grid* gd);
	void resolve_conflicts(void);
private:
	int n;		// Num of agents
	Grid* grid;
	vector<agent_t> agentlist;	// List of agents
	vector<vector<int>> groups;	// Independent groups
};

#endif	// MAPF_H
