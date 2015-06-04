/* Written by Brandon Wu */
#include "test.h"
#include "Globals.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	//testSearch3();
	//return 0;
	if (argc == 1) return -1;
	string file_t(argv[1]);
	mapftest("../tests/" + file_t);
	return 0;
}

