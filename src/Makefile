TARGET=mapf
CC=g++
CFLAGS=-g -Wall -Wextra -w

all: state grid
	${CC} ${CFLAGS} main.cpp *.o -o ${TARGET} 

debug:
	${CC} ${CFLAGS} -c debug.cpp

grid:
	${CC} ${CFLAGS} -c Grid.cpp
state:
	${CC} ${CFLAGS} -c State.cpp

main:
	${CC} ${CFLAGS} -c main.cpp
clean:
	rm *.o ${TARGET}
