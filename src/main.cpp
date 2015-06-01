/* Written by Brandon Wu */
#include "Grid.h"
#include "State.h"
#include "Search.h"
#include "Bfs.h"
#include "Mapf.h"
#include "Globals.h"

#include <iostream>
using namespace std;

void testState1();
void testSearch1();
void testSearch2();
void testSearch3();
void testGrid1();
void testMapf1();
void testMapf2();
void testMapf_small();
void testBFS();
void testSearch4();

Point** gen_parr(int* list, int n);


void testBFS() { 
	Grid g("../grids/g2.txt");
	int arr[] = {0,1, 7, 2};
	Point* p = (Point*) arr;
	Bfs bfs(p, p+1, &g);
	cout << "BFS cost " << bfs.cost() << endl;
}
void testSearch4() {
	int init[] = {0,0};
	int goal[] = {4,4};
	Grid grid("../grids/g3.txt");
	
	Search s(1, (Point*) init, (Point*) goal, &grid);
	while(!s.expand());
	cout << "Num expansions= " << s.num_expansions() << endl;
	s.path(true);
}

bool chksolution(int init[], int goal[], int len, Grid* g);

//void gentest(int argc, char* argv[])
int main(int argc, char* argv[]) {

	//testMapf_small();

	if (argc == 1) return -1;
	
	string path_g(argv[1]);
	string path_a(argv[2]);
	int num_agents = -1;

	Point** states = readpos_agent(path_a,num_agents);
	Grid grid("../grids/" + path_g);
/*
	if (num_agents == -1) return -1;
	for (int i=0; i<num_agents; i++) {
		Bfs bfs(&states[0][i], &states[1][i], &grid);

		if (bfs.cost() > 100000)
			cout << "No solution for agent " << i << endl;
		else cout << "Cost for agent " << i << " "  << bfs.cost() << endl;

	}*/
	chksolution((int*)states[0], (int*)states[1], num_agents, &grid);
	Mapf m(num_agents, states[0], states[1], &grid);
	while (m.resolve_conflicts());
	cout << "\tTotal Nodes Expanded: " << m.num_expansions() << endl;	

	delete [] states[0];
	delete [] states[1];
	delete [] states;
	//testGrid1();
	//testSearch1();
	//testSearch2();
	//testSearch3();
	//testBFS();
	//testMapf_small();
	//testMapf2();
	//testBFS();
	//testSearch4();
	return 0;
}

void testMapf_small() {
	int init[] = {0,0,0,2};
	int goal[] = {0,1,1,0};
	Grid grid("../grids/g4.txt");
	
	Search s(2, (Point*) init, (Point*) goal, &grid);
	while(!s.expand());
	s.path(true);
	cout << "------------------\n";
	/*Mapf m(2, (Point*) init, (Point*) goal, &grid);
	while(m.resolve_conflicts());*/

}
