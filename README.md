# Introduction
An implementation of Multi-agent pathfinding using
A* with Operator Decomposition (OD). Written by Brandon Wu.

##Completed
* Naive A* algorithm that stores all nodes expanded. Implement iterative
deepening A* (IDA*) for lower space complexity.
* Path backtrace from goal to root enabled for n agents
* Multiple agent path finding with simple collision detection
* Smarter checking of post-move collision
* Prelim work for detecting conflict paths btw independent agents
* Independence Detection (ID) implemented in Mapf module. 
* Implemented True Distance Heuristic in Bfs module
* Changed open list to heap (verify performance)
* Changed parent node to be most recent std node to disallow reverse move
* Prune branches by disallowing moves in the reverse direction

##Todo
* Improve test bench that does not require recompile for changing
grids/agent positions
* Pre-compute true distance heuristic
* Timing and expansion metrics
* Reduce redundant node expansions across all iterations of ID
* More testing for ID implementation
* Multi-agent swap collisions
* Remove Memory leaks

##Bugs
List bugs here
