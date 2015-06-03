#!/usr/bin/python

import random as r
import time as t

def printgrid(matrix, path):
	f = open(path, 'w')
	dimX = len(matrix)
	dimY = len(matrix[0])
	
	for i in map(lambda x: dimY-1-x, range(dimY)):
		printrow = list()	
		for j in range(dimX):
			tmp = matrix[j][i]
			printrow.append(tmp)
		f.write(''.join([str(i) for i in printrow]) + '\n')
	f.close()

def printagents(agents, path):
	f = open(path, 'w')
	f.write(str(len(agents)/2)+"\n")
	for i in range(len(agents)):
		tmp =  str(agents[i][0]) + " " + str(agents[i][1]) + "\n"
		f.write(tmp)
	f.close()

def makegrid(dimX, dimY, p):
	grid = [[0 for j in range(dimY)] for i in range(dimX)]
	for i in range(dimX):
		for j in range(dimY):
			grid[i][j] = 1 if r.random() > p else 0
	return grid

def placeAgents(k, grid):	# Find start and end pos for k agents
	dimX = len(grid)
	dimY = len(grid[0])
	
	validPos = list()	# List of valid positions in the grid
	agentPos = list()
	
	for i in range(dimX):
		for j in range(dimY):
			if grid[i][j] is 1:
				validPos.append((i,j))
	#for i in range(len(validPos)):
	#	print validPos[i]

	for i in range(2*k):
		tmp = int(r.uniform(0,len(validPos)))
		agentPos.append(validPos[tmp])
		#print validPos[tmp]
		validPos.remove(validPos[tmp])

	return agentPos

def maketest(dimX, dimY, p, k, path_g, path_a):
	grid_t = makegrid(dimX, dimY, p)
	agents_t = placeAgents(k, grid_t)
	printgrid(grid_t, path_g)
	printagents(agents_t, path_a)

if __name__ == "__main__":
	
	r.seed(t.time())
	prefix = "t5_"
	gdir = "../grids/"
	adir = "../agents/"
	testfile = "../tests/t5.test"
	num_tests = 15
	
	dimX = 50
	dimY = 30
	num_agents = 4
	p = 0.4	# Probability of obstacle
	
	f = open(testfile, 'w')
	f.write("#num_tests="+str(num_tests)+"\tdim="+str(dimX)+"x"+str(dimY)+" num_agents="+str(num_agents)+" p="+str(p)+"\n")
	for i in range(num_tests):
		path_g = gdir + prefix + "g" + str(i) + ".txt"
		path_a = adir + prefix + "a" + str(i) + ".txt"
		f.write(prefix + "g" + str(i) + ".txt\n")
		f.write(prefix + "a" + str(i) + ".txt\n")
		maketest(dimX, dimY, p, num_agents, path_g, path_a)
	f.close()
	


