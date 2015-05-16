#include "Grid.h"
#include "State.h"
#include "Search.h"

#include <iostream>
using namespace std;

void testState1();
void testSearch1();

Point** gen_parr(int* list, int n);

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
	int list [] = {0, 4, 1, 1, 1, 4, 3, 3, 4, 0};
	Point** plist = gen_parr(list, 5);
	for (int i=0; i<4; i++) {
		Point* p = plist[i];
		cout << "(" << p->x << "," << p->y << ")\n";
	}

	Grid g(10,10,plist, 5);
	g.display();

	Point p1(0,0);
	Point g1(4,4);

	Search s(1, &p1, &g1, &g);

	while (!s.expand());
}

Point** gen_parr(int* list, int n) {
	Point** plist = new Point*[n];
	for (int i=0; i<n; i++)
		plist[i] = (Point*) (list+2*i);
	return plist;
}
