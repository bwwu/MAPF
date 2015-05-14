#include "Grid.h"
#include "State.h"

#include <iostream>
using namespace std;


int main() {
	Point p(1,1);
	State s(&p, 1);
	Move m(NORTH, 0);
	s.display();
	State c(1,s,m);
	c.display();


	cout << sizeof(State) << endl;
}
