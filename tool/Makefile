.PHONY: all clean

CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++17

ROOTSRC=../src
INC=../include 

all: genExpr

clean:
	rm -f *.o genExpr expr.h

genExpr: genExpr.cpp stringUtils.h
	$(CC) $(CFLAGS) -I. genExpr.cpp -o genExpr \
	&& \
	./genExpr .
