/* Written by Brandon Wu */

#include "Search.h"
#include <limits>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

Search::Search(int n, Point* init, Point* goal, Grid* g):
	n(n), init(init), grid(g), exp_cnt(1) {
	
	current = NULL;

	this->goal = new Point[n];
	for (int i=0; i<n; i++)
		this->goal[i] = goal[i];

	/*	Add initial state to open list */
	Node* tmp = new Node;
	tmp->p = NULL;
	tmp->s = new State(init, n);
	tmp-> f = tmp->s->h(goal);
	tmp->turn = 0;
	open.push_back(tmp);
	

	time(&start_t);
}

Search::~Search() {
	delete [] goal;
}

bool Search::expand(void) {
	//cout << "Expanding\n========\n";
	/* Choose node on open with min f cost */
	int min = std::numeric_limits<int>::max();
	Node* nd = NULL;		//Node to expand

	auto it = open.begin();
	auto del = open.begin();

	for (it; it < open.end(); it++) {
		if((*it)->f <= min) {
			min = (*it)->f;
			del = it;
			nd = *it;
		}
	}

	if (!nd) { 
		cout << "ERROR: NULL chosen for expansion\n";
		return false;
	}
	open.erase(del);	// Remove from open list

	/* Check if node chosen for exp is goal */
	if (is_goal(nd))
		return true;

	/* Get adj list for position of agent about to move */
	int turn = nd->turn;

	bool* valid_m = nd->s->valid_moves(turn, grid);
	for (int i=0; i<DIM+1;i++) {
		if (valid_m[i]) 
			open.push_back(generate(nd,i));
	}

	delete [] valid_m;
	return false;
}

Node* Search::generate(Node* p, int dir) {
	Node* child = new Node;
	Move m((Card)dir, p->turn);
	
	exp_cnt++;	//Increment num of nodes expanded

	child->p = p;
	child->turn = (p->turn+1 == n) ? 0 : p->turn+1;
	child->s = new State(n, *(p->s), m);
	child->f = p->s->g() + child->s->h(goal);
	child->dir = dir;

	/****Debug****
	cout << "Generating move for Agent: " + (p->turn) <<
		" In direction: " << dir << "\n\tFrom: ";
	child->p->s->display();
	cout << "\tTo: ";
	child->s->display();
	cout << "\t h(n) = " << child->f << endl;
	**** Debug ****/

	return child;
}

/* Return true if node is a goal node */
bool Search::is_goal(Node* nd) {
	for (int i=0; i<n; i++) {
		Point* p = nd->s->get_pos(i);
		if (goal[i].x != p->x || goal[i].y != p->y)
			return false;
	}

	time_t end_t = time(NULL);
	double diff_t = difftime(end_t, start_t);
	current = nd;	// Set goal node
	cout << fixed;
	cout << "Found goal with cost " << nd->s->g() << "!\n";
	cout << "\tElapsed Time = " << setprecision(8) << diff_t << "s\n";
	cout << "\tNum Expansions = " << num_expansions() << " nodes\n";
	
	/*
	vector<int>* moves =  backtrace(nd);
	for (int i=0; i<n; i++) {
		cout << "Player " << i <<  " pos\n";
		int* arr = reconstruct_path(i, moves[i]);
		for (int j=0; j< moves[i].size()+1; j++) {
			cout << arr[j] << " ";
		}
		cout << endl;
		delete [] arr;
	}
	delete [] moves; */
	return true;
}

vector<int>* Search::backtrace(Node* walk) {
	/* Returns array of vectors of moves for each agent
	 *	moves[i] is a vector of moves for agent 'i'
	 */
	if (!walk) return NULL;
	
	vector<int>* agent_moves = new vector<int>[n];
	vector<int> moves;
	do {
		moves.push_back(walk->dir);	// dir that the parent
		walk = walk->p;
	} while (walk->p);

	int blocksize = moves.size()/n;
	for (int i=0; i<n; i++) {
		cout << "\nPlayer " << i << " moves\n";
		for (int j = blocksize-1; j>=0; j--) {
			int it = moves[j*n+(n-1-i)];
			agent_moves[i].push_back(it);
			cout << dir2str(it) + "\n";
			/*
			switch((Card) it ) {
			case NORTH:
				cout << "North\n";
				break;
			case SOUTH:
				cout << "South\n";
				break;
			case EAST:
				cout << "East\n";
				break;
			case WEST:
				cout << "West\n";
				break;
			case WAIT:
				cout << "Wait\n";
			} */
		}
	}
	return agent_moves;
}

int*	Search::reconstruct_path(int agent, const vector<int>& tr) {
	if (agent >= n) return NULL;

	/*
	cout << "Trace\n";
	for (int i=0; i<tr.size(); i++) 
		cout << tr[i] << " ";
	cout << endl; */

	int* path = new int[tr.size()+1];
	Point init_s = init[agent];
	
	for (int i=0; i<tr.size(); i++) {
		path[i] = grid->hash_pt(&init_s);
		init_s = move_dir(&init_s, tr[i]);
	}
	path[tr.size()] = grid->hash_pt(&init_s);
	return path;
}

vector<int>* Search::path(bool print=false) {
	if (!current) return NULL;		
	
	vector<int>*	pos = new vector<int>[n];
	vector<int>*	moves = backtrace(current);
	
	for (int i=0; i<n; i++) {
		if (print) cout << "Player " << i << endl;
		int* arr = reconstruct_path(i, moves[i]);
		for (int j=0; j<moves[i].size()+1; j++) {
			if (print) cout << arr[j] << " ";
			pos[i].push_back(arr[j]);
		}
		if (print) cout << endl;
		delete [] arr;
	}
	return pos;	// Return list of pos for ea agent in search
}
