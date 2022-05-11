#include <iostream>
#include <string>

#include "debug.h"

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