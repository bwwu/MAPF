TARGET=mapf
CC=g++
CFLAGS=-g -Wall -Wextra -w -std=c++11

all: state grid search
	${CC} ${CFLAGS} main.cpp *.o -o ${TARGET} 

debug:
	${CC} ${CFLAGS} -c debug.cpp
grid:
	${CC} ${CFLAGS} -c Grid.cpp
state:
	${CC} ${CFLAGS} -c State.cpp
search:
	${CC} ${CFLAGS} -c Search.cpp Mapf.cpp Bfs.cpp
clean:
	rm *.o ${TARGET}
