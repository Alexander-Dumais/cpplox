#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include "scanner.h"

struct source_pairs 
{
    const std::string source;
    const std::string describe;

    source_pairs() = delete;

    source_pairs(std::string source, std::string describe): 
        source(source), describe(describe){}
};

std::string toString(Scan::Scanner &scanner) 
{
    std::stringstream ss;
    for(auto t : scanner.tokens)
    {
        ss << t.toString() << " ";
    }
    
    return ss.str();
}

int main()
{
    //TODO: Put these tests into a header with `expected` and `result` test structure. Only print failures.
    static const std::vector<source_pairs> input = {
        {"( ) { } , . - + ; / * ", "Single-character tokens"},
        {"! != = == > >= < <=", "One or two character tokens"},
        {"example  \"string\"  8", "Literals (Identifier, string, number)"},
        {"\"string1\" \"string2\"", "Multiple strings"},
        {"and class else false fun for if nil or print return super this true var while", 
        "Keywords"},
        {"var language = \"lox\";", "Realistic line of code."},
        {"var language = \"lox\";\n//Prints anything\nprint(language);\nprint(\"goodbye!\")\n", "Multiline file"},
        {"//Comment \r", "White spaces and comments"},
        {"\n ", "White spaces and comments"},
        {"\t                 \n", "White spaces and comments"},
        {"\0", "Lox EOF"},
    };

    std::cout << "Testing the following: \n\n";
    for (auto line : input)
    {
        std::cout << line.describe << "\n";
        
        Scan::Scanner scanner(line.source);
        scanner.scanTokens();
        
        std::cout << "types and lexemes:\n" << scanner << "\n";
        for (auto it = scanner.tokens.begin(); it != scanner.tokens.end(); ++it)
        {
            if (it != scanner.tokens.begin())
                std::cout << ", ";
            std::cout << it->lexeme;
        }
        std::cout << "\n\n";
    }
}