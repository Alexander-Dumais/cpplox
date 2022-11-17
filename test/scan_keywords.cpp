#include <iostream>
#include "scanner.h"

int main()
{
    //auto tok = Tok::Token(Tok::TokenType::STRING, "Example", "Example", 1);

    std::cout << "literal" << "\t-    " << "TYPE" << "\n\n";
    for (auto v : Scan::keywords)
    {
        std::cout << v.first << "\t-    " << v.second << "\n";
    }
}