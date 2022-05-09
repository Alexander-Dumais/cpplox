#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#define DEBUG_ON 1

void println(string s);
void DEBUG(string s);
void runFile(char *filename);
void runPrompt();

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
        DEBUG( "Entering runPrompt()\n" );
        runPrompt();
    }
}

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

void run(string source) {
    
}
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

void runPrompt()
{
    string line;
    while(getline(std::cin, line)) {
        DEBUG(line);
        //run(line);
    }

    DEBUG("TODO: Implement runPrompt()");
}