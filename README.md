# Introduction
An implementation of Multi-agent pathfinding using
A* with Operator Decomposition (OD). Written by Brandon Wu.

##Current Metrics
Node Generation Time:	
74,120 Nodes/second	(5/29/15)
12,625 Nodes/second	(6/1/15)	-- Smarter duplicate detection on large maps

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
* Prune branches by disallowing moves in the reverse direction -- [REMOVED]
* Added duplicate detection for BFS search
* Added test generation suite

##Todo
* Make struct of test vectors {grid name, agents, num exp, time}
* Pre-compute true distance heuristic
* Reduce redundant node expansions across all iterations of ID
* More testing for ID implementation
* Remove Memory leaks

##Bugs
* Some maps cannot be solved although a solution supposedly exists
* There is no way to kill a search that is taking too long
* preprocessed BFS causes issues
