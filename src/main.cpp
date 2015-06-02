/* Written by Brandon Wu */
#include "test.h"
#include "Globals.h"
#include <iostream>
using namespace std;


//bool run_mapf(string path_g, string path_a);

int main(int argc, char* argv[]) {

	if (argc == 1) return -1;
	mapftest(argv[1]);
	return 0;
}

