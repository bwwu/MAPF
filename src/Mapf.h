/* Written by Brandon Wu */
#ifndef MAPF_H
#define MAPF_H
#include "Distance.h"
#include "Search.h"
#include "Grid.h"
#include "State.h"

#include <unordered_map>
using namespace std;

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
	~Mapf();
	int resolve_conflicts(void);

	int	num_expansions(void);
	time_t	get_time(void);
	int	get_collisions(void);
	int	cost(void);	// Solution Cost
private:
	int n;		// Num of agents
	int num_exp;	// Total node exp
	int collisions;	// Num of collisions
	int max_cost;

	time_t	start_t;
	time_t	diff_t;	// Total time elapsed

	Distance* dlt;	//Distance lookup table
	Grid* grid;
	Apos_t lastConflict;
	
	unordered_map<int,Apos_t>* cat;	// List of avoidance tables
	vector<agent_t> agentlist;	// List of agents
	vector<vector<int>> groups;	// Independent groups

	int group_conflict(vector<int>* g1,vector<int>* g2,int len1,int len2);
	int path_conflict(vector<int>* p1, vector<int>* p2, int len);
};

inline
int Mapf::num_expansions(void) {
	return num_exp;
}

inline
time_t Mapf::get_time(void) {
	return diff_t;
}

inline
int Mapf::get_collisions(void) { return collisions; }
inline
int Mapf::cost(void) {	return max_cost;	}
#endif	// MAPF_H
