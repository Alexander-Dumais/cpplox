#include <iostream>

#include "run.h"
#include "debug.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc > 2)
    { // file name is always the first value
        cout << "Usage: cpplox [script]" << endl;
        return 0;
    }
    else if (argc == 2)
    {
        DEBUG( "Entering runFile()\n" );
        runFile(argv[argc - 1]);
    }
    else
    {
        DEBUG( "Entering runPrompt()\n" );
        runPrompt();
    }
}