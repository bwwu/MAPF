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

##Todo
* Make open list a heap
* Store most recent standard node as parent to enable reverse move 
detection
* Pre-compute true distance heuristic
* Timing and expansion metrics
* Reduce redundant node expansions across all iterations of ID
* More testing for ID implementation
* Multi-agent swap collisions
* Prune branches (disallow reverse move)

##Bugs
List bugs here
