#include "Mapf.h"

Mapf::Mapf(int n, Point* s_init, Point* s_goal, Grid* gd): n(n), grid(gd) {
	/* Begin with n singleton groups */
	for (int i=0; i<n; i++) {
		// Create an agent_t struct for each agent and group for ea agent
		agentlist.push_back(agent_t(i, s_init[i], s_goal[i]));
		vector<int> list;
		list.push_back(i);
		groups.push_back(list);
	}
}

void Mapf::resolve_conflicts(void) {
	// For each group find independent soln and look for conflicts
	for (int i=0; i< groups.size(); i++) {
		int len = groups[i].size();
		Point* s_init = new Point[len];
		Point* s_goal = new Point[len];
	
		// Populate init and goal states for members of the group	
		for (int j=0; j<len; j++) {
			int agent_id = groups[i][j];
			s_init[j] = agentlist[agent_id].init;
			s_goal[j] = agentlist[agent_id].goal;
		}
		// Find solution on group
		Search s(len, s_init, s_goal, grid);
		while (!s.expand());

		vector<int>* g_paths = s.path();
		
		cout << "Group " << i << endl;
		if (g_paths) {
			for (int j=0; j<len; j++) {
				for (int k=0; k<g_paths[j].size(); k++) {
					cout << g_paths[j][k] << " ";
				}
				cout << endl;
			}
		}
		
		delete [] s_init;
		delete [] s_goal;
	}
}
