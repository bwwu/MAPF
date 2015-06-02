#ifndef TEST_H
#define TEST_H

#include "Grid.h"
#include "State.h"
#include "Search.h"
#include "Bfs.h"
#include "Mapf.h"
#include "Globals.h"

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
bool chksolution(int init[], int goal[], int len, Grid* g);

#endif // TEST_H
