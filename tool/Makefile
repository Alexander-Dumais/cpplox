# Alexander Dumais | 2023-2025

.PHONY: all clean

CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++17

OBJ=build/obj

all: genExpr

clean:
	rm -f genExpr expr.h
	rm -rf build/

$(OBJ):
	mkdir -p $(OBJ)

$(OBJ)/genExpr.o: genExpr.cpp stringUtils.h | $(OBJ)
	$(CC) $(CFLAGS) -c -I. $< -o $@

# compile genExpr and run it in this directory
# Without special variables, for fun
genExpr: $(OBJ)/genExpr.o
	$(CC) $(CFLAGS) -I. $(OBJ)/genExpr.o -o genExpr \
	&& \
	./genExpr .
