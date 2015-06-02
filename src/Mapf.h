/* Written by Brandon Wu */
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

/* Implements independence detection */
class Mapf {
public:
	Mapf(int n, Point* s_init, Point* s_goal, Grid* gd);
	bool resolve_conflicts(void);

	int num_expansions(void);
	time_t	get_time(void);
private:
	int n;		// Num of agents
	int num_exp;	// Total node exp
	time_t	start_t;
	time_t	diff_t;	// Total time elapsed

	Grid* grid;
	vector<agent_t> agentlist;	// List of agents
	vector<vector<int>> groups;	// Independent groups

	bool group_conflict(vector<int>* g1,vector<int>* g2,int len1,int len2);
	bool path_conflict(vector<int>* p1, vector<int>* p2, int len);
};

inline
int Mapf::num_expansions(void) {
	return num_exp;
}

inline
time_t Mapf::get_time(void) {
	return diff_t;
}
#endif	// MAPF_H
