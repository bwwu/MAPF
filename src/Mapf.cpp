/* Written by Brandon Wu */
#include "Mapf.h"
#include "Distance.h"
#include <iomanip>
using namespace std;
static int conflict_watch = 0;

Mapf::Mapf(int n, Point* s_init, Point* s_goal, Grid* gd): n(n), grid(gd) {
	num_exp = 0;
	collisions = 0;
	time(&start_t);
	dlt = new Distance(grid);

	/* Begin with n singleton groups */
	for (int i=0; i<n; i++) {
		// Create an agent_t struct for each agent and group for ea agent
		agentlist.push_back(agent_t(i, s_init[i], s_goal[i]));
		vector<int> list;
		list.push_back(i);
		groups.push_back(list);
	}
}

Mapf::~Mapf() {
	delete dlt;
}

// Resolve conflicts among groups. If conflicts exist, merge groups
int Mapf::resolve_conflicts(void) {
	cout << "resolve_conflicts start\n";
	// For each group find independent soln and look for conflicts
	bool conflicts = false;	// Indicates whether conflicts found
	vector<int>** id_paths = new vector<int>*[groups.size()];
	int oldlen = groups.size();
	
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
		cout << "starting search groupsize " << len << endl;
		Search s(len, s_init, s_goal, grid, dlt);
		int result = 0;
		do {
			result = s.expand();
		} while (!result);
		cout << "***********\nDone\n";

		if (result == 2) {
			delete [] s_init;
			delete [] s_goal;
			delete [] id_paths;
			return 2;
		}

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
				cout << "   Agent: " << agent_id << "\t";
				for (int k=0; k<g_paths[j].size(); k++) {	// For ea move
					cout << g_paths[j][k] << " ";
				}
				cout << endl;
			}
		}
		cout << "resolve_conflicts end\n";
		delete [] s_init;
		delete [] s_goal;
	}

	cout << "group conflict resolution start\n";
	for (int i=0; i<num_groups-1; i++) {
		int len1 = groups[i].size();
		for (int j=i+1; j<num_groups && !conflicts; j++) {	
			// For ea pair of groups
			int len2 = groups[j].size();
			
			/* If there is a path conflict between groups i and j */
			if (group_conflict(id_paths[i], id_paths[j], len1, len2)) {
				conflicts = true;
			
				/* Merge the groups */
				cout << "Conflict found between Group "<<i<<" and "<<j<<endl;
				collisions++;
				vector<int>* g1 = &groups[i];
				vector<int>* g2 = &groups[j];
				g1->insert(g1->end(), g2->begin(), g2->end());
				
				auto it = groups.begin() + j;
				groups.erase(it);

			}
		}
	}
	if (!conflicts) {
		time_t end_t = time(NULL);
		diff_t = difftime(end_t, start_t);
	}

	cout << "Group conflict resolution end\n";
	for (int i=0; i<num_groups; i++)
		delete [] id_paths[i];

	delete [] id_paths;
	return (conflicts) ? 1 : 0;
}

bool
Mapf::group_conflict(vector<int>* g1,vector<int>* g2,int len1,int len2) {
	if (!(g1&&g2)) return false;

	//cout << "group_conflicts start\n";
	/* Use len of shortest path */
	int plen = (g1[0].size() > g2[0].size()) ? g2[0].size() : g1[0].size();

	/* Take cross product
	 * Consider all pairs of agents (u, v) where u in g1 and v in g2 */
	for (int i=0; i<len1; i++) {
		for (int j=0; j<len2; j++) {
			if (path_conflict(&g1[i], &g2[j], plen))
				return true;	
		}
	}
	/* No path conflict between groups g1 and g2*/
	
	//conflict_watch++;
	//cout << "group_conflicts end\n";
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
