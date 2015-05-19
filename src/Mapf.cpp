/* Written by Brandon Wu */
#include "Mapf.h"

Mapf::Mapf(int n, Point* s_init, Point* s_goal, Grid* gd): n(n), grid(gd) {
	num_exp = 0;
	/* Begin with n singleton groups */
	for (int i=0; i<n; i++) {
		// Create an agent_t struct for each agent and group for ea agent
		agentlist.push_back(agent_t(i, s_init[i], s_goal[i]));
		vector<int> list;
		list.push_back(i);
		groups.push_back(list);
	}
}

// Resolve conflicts among groups. If conflicts exist, merge groups
bool Mapf::resolve_conflicts(void) {
	// For each group find independent soln and look for conflicts

	bool conflicts = false;	// Indicates whether conflicts found
	vector<int>** id_paths = new vector<int>*[groups.size()];
	
	int num_groups = groups.size();
	
	for (int i=0; i< num_groups; i++) {	// For ea group
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
	
		num_exp += s.num_expansions();

		vector<int>* g_paths = s.path(false);	// Get the soln path
		id_paths[i] = g_paths; 


		/* TODO: Determine conflicts across groups 
			then proceed to record positions if no conflicts are found
		*/


		cout << "Group " << i << endl;
		if (g_paths) {
			for (int j=0; j<len; j++) {	// For ea agent in the group
				int agent_id = groups[i][j];
				//if (agentlist[agent_id].path)
					//delete agentlist[agent_id].path;

				//vector<int>* a_path = new vector<int>;
				for (int k=0; k<g_paths[j].size(); k++) {	// For ea move
					cout << g_paths[j][k] << " ";
					//a_path->push_back(g_paths[i][k]);	// Update agent's soln
				}
				cout << endl;
				//agentlist[agent_id].path = a_path;
			}
		}

		//delete [] g_paths;
		delete [] s_init;
		delete [] s_goal;
	}

	for (int i=0; i<num_groups-1; i++) {
		int len1 = groups[i].size();
		for (int j=i+1; j<num_groups; j++) {	// For ea pair of groups
			int len2 = groups[j].size();
			
			/* If there is a path conflict between groups i and j */
			if (group_conflict(id_paths[i], id_paths[j], len1, len2)) {
				conflicts = true;
			
				/* Merge the groups */
				cout << "Conflict found between Group " << i << " and " << j;
				cout << ". Merging...\n";
				vector<int>* g1 = &groups[i];
				vector<int>* g2 = &groups[j];
				g1->insert(g1->end(), g2->begin(), g2->end());
				
				auto it = groups.begin() + j;
				groups.erase(it);

			}
		}
	}

	for (int i=0; i<num_groups; i++)
		delete [] id_paths[i];
	delete [] id_paths;
	return conflicts;
}

bool
Mapf::group_conflict(vector<int>* g1,vector<int>* g2,int len1,int len2) {
	if (!(g1&&g2)) return false;

	/* Use len of shortest path */
	int plen = (g1[0].size() > g2[0].size()) ? g2[0].size() : g1[0].size();

	/* Take cross product
	 * Consider all pairs of agents (u, v) where u in g1 and v in g2 */
	for (int i=0; i<len1; i++) {
		for (int j=0; j<len2; j++) {
			if (path_conflict(&g1[i], &g2[i], plen))
				return true;	
		}
	}
	/* No path conflict between groups g1 and g2*/
	return false;
}

bool
Mapf::path_conflict(vector<int>* p1, vector<int>* p2, int len) {
	/* Return true if there is conflict on path of 2 agents */
	for (int i=0; i<len; i++)
		if (p1->at(i) == p2->at(i)) {
			cout << "Conflict at t = " << i << ". Value is " << p1->at(i) 
				<< endl;
			return true;
		}

	return false;
}
