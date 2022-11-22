#include <iostream>
#include "scanner.h"

struct source_pairs {
    const std::string source;
    const std::string describe;

    source_pairs() = delete;

    source_pairs(std::string source, std::string describe): 
        source(source), describe(describe){}
};

int main()
{
    static const std::vector<source_pairs> input = {
        //{"( ) { } , . - + ; / * ", "Single-character tokens"},
        //{"! != = == > >= < <=", "One or two character tokens"},
        //{"example  \"string\"  8", "Literals (Identifier, string, number)"},
        //{"and class else false fun for if nil or print return super this true var while", 
        //"Keywords"},
        //{"//Comment \r", "White spaces and comments"},
        //{"\n ", "White spaces and comments"},
        //{"\t                 \n", "White spaces and comments"}
        //{"\0", "Lox EOF"}
        {"8", "number"},
        {"and, or,or", "keyword/ifentifier testing"},
        //{"or and", "or"},
    };

    for (auto line : input) {
        std::cout << line.describe << "\n";
        
        Scan::Scanner scanner(line.source);
        scanner.scanTokens();
        
        std::cout << scanner << "\n\n";
    }
}