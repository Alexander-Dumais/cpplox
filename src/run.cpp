#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include "run.h"
#include "debug.h"
#include "scanner.h"

using namespace std;

static bool hadError = false;

/**
 * @brief report an error to standard out
 *
 * @param line of the error
 * @param where source of error
 * @param message error message
 *
 * TODO: It's possible to have very precise error reports where the exact token causing a parsing problem is identified.
 *       I would like to do this in the near future.
 *
 * ideal example:
 *  Error: Unexpected "," in argument list.
 *
 *   15 | function(first, second,);
 *                              ^-- Here.
 */
void report(int line, string where, string message)
{
    std::cout << "[line " << line << "] Error " << where << ": " << message << std::endl;
    hadError = true;
}

/**
 * @brief Report an error with the location and a custom message
 *
 * @param line of the error
 * @param message describing the error
 */
void error(int line, string message)
{
    report(line, "", message);
}

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

    // For now just print the tokens
    DEBUG("Scanned Tokens: ", scanner);
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
            if (hadError)
                exit(1);
        }
        file.close();
    }
    catch (std::ifstream::failure &e)
    {
        // If the file.exceptions is too broad, this will be triggered due to character like EOF.
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
    DEBUG("Input line of lox code (currently operators only):", "");
    while (getline(std::cin, line))
    {
        DEBUG("Processing line: ", line);
        run(line);
        hadError = false; // If in a repl, we dont want one error to break the entire repl.
        DEBUG("Input line of lox code (currently operators only):", "");
    }
}