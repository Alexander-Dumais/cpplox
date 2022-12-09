#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include "run.h"
#include "debug.h"
#include "scanner.h"
#include "lox_error.h"

using namespace std;

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
            if (lox_error::hadError)
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
    try {
        string line;
        DEBUG("Input line of lox code:", "");
        while (getline(std::cin, line))
        {
            DEBUG("Processing line: ", line);
            run(line);
            lox_error::hadError = false; // If in a repl, we dont want one error to break the entire repl.
            DEBUG("Input line of lox code:", "");
        }
    } 
    catch (std::iostream::failure &e)
    {
        std::cerr << "Exception reading line in runPrompt." << std::endl;
    }
}