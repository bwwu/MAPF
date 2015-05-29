TARGET=mapf
CC=g++
CFLAGS=-g -Wall -Wextra -w -std=c++11 -O2
SRCS=Globals.cpp Grid.cpp State.cpp Search.cpp Mapf.cpp Bfs.cpp test.cpp

ifdef GPROF
CFLAGS += -pg
endif

all: default
	${CC} ${CFLAGS} main.cpp *.o -o ${TARGET} 
debug:
	${CC} ${CFLAGS} -c debug.cpp
default:
	${CC} ${CFLAGS} -c ${SRCS}
clean:
	rm *.o ${TARGET}
