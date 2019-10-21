CFLAGS=-std=c99 -Wall -Wextra -pedantic
CCFLAGS=-std=c++11 -pedantic -Wall

all: tail tail2

tail: tail.c
	gcc ${CFLAGS} tail.c -o tail

tail2: tail2.cc
	g++ ${CCFLAGS} tail2.cc -o tail2

zip:
	zip xburda13.zip *.c *.cc Makefile
