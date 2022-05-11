#include <iostream>
#include <string>

#include "debug.h"

#define DEBUG_ON 1

using namespace std;

void println(string s)
{
    cout << s << endl;
}

void DEBUG(string s)
{
    if (DEBUG_ON)
    {
        cout << "DEBUG: " << s << endl;
    }
}