#pragma once

#include "scanner.h"

//TODO turn this into a typical debug switch. Use a macro instead of this. When done I can remove the debug.cpp file.
//c++ will optomize DEBUG(m, s) calls away if the function body is empty.
// #define _DEBUG 1 
// #if _DEBUG
//     void DEBUG(string message, string s) { cout << message << s << endl; }
// #else
//     void DEBUG(string message, string s) {}
// #endif

#define DEBUG_ON 1

void println(std::string s);
void DEBUG(std:: string m, std::string s);
void DEBUG(std:: string m, Scan::Scanner &s);