#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include "run.h"
#include "debug.h"
#include "scanner.h"

using namespace std;

//TODO: Add error handling here
//   static void error(int line, String message) {
//     report(line, "", message);
//   }

//Java implementation from textbook
//   private static void report(int line, String where,
//                              String message) {
//     System.err.println(
//         "[line " + line + "] Error" + where + ": " + message);
//     hadError = true;
//   }


/**
 * @brief Scan the source, tokenize the source, then run the source
 * 
 * @param source A line of Lox source code
 */
void run(string source)
{
    DEBUG("In run()", "");
    Scan::Scanner scanner(source);
    std::vector<Tok::Token> tokens = scanner.scanTokens();

    //For now just print the tokens
    std::cout << "Scanned Tokens: " << scanner << std::endl;
}

/**
 * @brief interpret an input file
 *
 * @param filename the name of the input file
 */
void runFile(char *filename)
{
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    try
    {
        file.open(filename);
        string line;
        while (getline(file, line))
        {
            DEBUG("Processing line: ", line);
            run(line);
        }
        file.close();
    }
    catch (std::ifstream::failure e)
    {
        //If the file.exceptions is too broad, this will be triggered due to character like EOF.
        std::cerr << "Exception opening, reading or closing file." << std::endl;
    }
}

/**
 * @brief interpret each prompt from a user or input stream
 *
 */
void runPrompt()
{
    string line;
    while (getline(std::cin, line))
    {
        DEBUG("Processing line: ", line);
        run(line);
    }
}