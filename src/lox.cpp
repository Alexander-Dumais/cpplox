#include <iostream>

#include "run.h"

using namespace std;

/**
 * @brief Entry point for the Lox interpreter
 * 
 * @param argc num arguments
 * @param argv arguments. 0 arguments runs the raw interpreter, 2 runs the interpreter with input.
 * @return int 
 */
int main(int argc, char **argv)
{
    if (argc > 2) //Too many arguments
    {
        cout << "Usage: cpplox [script]" << endl;
        return 1;
    }
    else if (argc == 2) //A flag and a filename runs lox with the input file
    {
        cout << "Entering runFile()" << endl;
        runFile(argv[argc - 1]);
        return 0;
    }
    else //No arguments runs the lox interpreter similar to how running Python without arguments spins up a python interpreter
    {
        cout << "Entering runPrompt()" << endl;
        runPrompt();
        return 0;
    }
}