#include <iostream>
#include "scanner.h"

namespace Scan {
    
    /**
     * @brief Construct a new Scanner:: Scanner object
     * 
     * @param source The source Lox code to be scanned
     */
    Scanner::Scanner(std::string source): source(source) {}

    std::vector<Tok::Token> Scanner::scanTokens() {
        // while (!isAtEnd()) {
        //     start = current;
        //     scanToken();
        // }

        tokens.emplace_back(Tok::TokenType::EOF_LOX, "", nullptr, line);
        //###################TODO: ################# Finish function and implement its dependencies 
    }
}