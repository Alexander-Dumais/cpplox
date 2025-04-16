.PHONY: all clean

CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++17

ROOTSRC=../src
INC=../include 

all: genAST

clean:
	rm -f *.o genAST expr.h

genAST: genAST.cpp stringUtils.h
	$(CC) $(CFLAGS) -I. genAST.cpp -o genAST \
	&& \
	./genAST .
