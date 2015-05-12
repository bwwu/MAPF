TARGET=mapf
CC=g++
CFLAGS=-g -Wall -Wextra

all: state
	${CC} ${CFLAGS} *.o -o ${TARGET} 

debug:
	${CC} ${CFLAGS} -c debug.cpp

state:
	${CC} ${CFLAGS} -c State.cpp

main:
	${CC} ${CFLAGS} -c main.cpp
clean:
	rm *.o ${TARGET}
