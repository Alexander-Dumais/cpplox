#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "debug.h"
#include "token.h"

using namespace std;

/**
 * @brief Scan the source, tokenize the source, then run the source
 * 
 * @param source A line of Lox source code
 */
void run(string source)
{
    // Java equivalent
    // Scanner scanner = new Scanner(source);
    // List<Token> tokens = scanner.scanTokens();

    // // For now, just print the tokens.
    // for (Token token : tokens) {
    //   System.out.println(token);
    // }
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
            DEBUG(line);
            // run(line);
        }
        file.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Exception opening, reading or closing file." << std::endl;
    }

    DEBUG("TODO: Implement runFile().");
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
        DEBUG(line);
        // run(line);
    }

    DEBUG("TODO: Implement runPrompt()");
}