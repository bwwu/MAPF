#include "Grid.h"
#include "State.h"
#include "Search.h"

#include <iostream>
using namespace std;

void testState1();
void testSearch1();

int main() {
	testSearch1();
	return 0;
}


void testState1() {
	Point p(1,1);
	State s(&p, 1);
	Move m(NORTH, 0);
	s.display();
	State c(1,s,m);
	c.display();


	cout << sizeof(State) << endl;
}

void testSearch1() {
	Grid g(10,10,NULL,0);
	g.display();

	Point p1(0,0);
	Point g1(4,4);
	Search s(1, &p1, &g1, &g);
	s.expand();
	s.expand();
	s.expand();
	s.expand();
}
