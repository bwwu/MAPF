TARGET=mapf
CC=g++
CFLAGS=-g -Wall -Wextra -std=c++11 -w
SRCS=Globals.cpp Grid.cpp State.cpp Search.cpp Mapf.cpp Bfs.cpp test.cpp
TRASH=${TARGET}

ifdef GPROF
CFLAGS += -pg -O2
TRASH += gmon.out
endif

all: default
	${CC} ${CFLAGS} main.cpp *.o -o ${TARGET} 
debug:
	${CC} ${CFLAGS} -c debug.cpp
default:
	${CC} ${CFLAGS} -c ${SRCS}
clean:
	rm *.o ${TRASH}
