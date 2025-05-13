# Copyright Alexander Dumais
# cpplox build script

SRCS=debug.cpp token.cpp scanner.cpp lox.cpp run.cpp 
SRCS:=$(addprefix src/, $(SRCS))
OBJS=$(patsubst src/%.cpp, build/%.o, $(SRCS))

CC=g++
CFLAGS=-std=c++2a -Wall -Wextra -pedantic
CPPFLAGS=-g
.PHONY: all clean

all: cpplox

clean:
	rm -f ./cpplox
	rm -rf ./bin ./build

bin:
	mkdir -p bin

build:
	mkdir -p build

build/%.o: src/%.cpp | build
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -I./include/

bin/cpplox: $(OBJS) | bin
	$(CC) $(CFLAGS) -o bin/cpplox -I./include $(OBJS)

objects: $(OBJS)

cpplox: bin/cpplox
	ln -s bin/cpplox ./cpplox 

