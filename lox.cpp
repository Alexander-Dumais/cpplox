#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void println(string s)
{
    cout << s << endl;
}

void runFile(char *filename)
{
    std::ifstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    //char *chars;

    try{
        file.open(filename);
        while (!file.eof()) {
            //char(file.get()) >> chars;
            cout << char(file.get()) << endl;
        }
        file.close();
        
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Exception opening, reading or closing file." << std::endl;
    }

    //cout << chars << endl;

    println("##########TODO: Implement runFile().");
    println(filename);
}

void runPrompt()
{
    println("##########TODO: Implement runPrompt()");
}

int main(int argc, char **argv)
{
    if (argc > 2)
    { // file name is always the first value
        cout << "Usage: cpplox [script]" << endl;
        return 0;
    }
    else if (argc == 2)
    {
        runFile(argv[argc - 1]);
    }
    else
    {
        runPrompt();
    }
}

/*
package com.craftinginterpreters.lox;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

*/