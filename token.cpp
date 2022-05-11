#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

#include "token.h"

namespace Tok {

    Token::Token() {
        assert(("number of tokens does not match the number of TokenTypes", tokenTypes.size() == (int)TokenType(EOF_LOX) + 1));
        std::cout << "Created tmpty Token" << std::endl;
    }

    Token::Token(TokenType type, std::string lexeme, void* literal, int line) 
        : type(type), lexeme(lexeme), literal(literal), line(line)
    {
        assert(("number of tokens does not match the number of TokenTypes", tokenTypes.size() == (int)TokenType(EOF_LOX) + 1));
        std::cout << "Created Token with non-empty constructor" << std::endl;
    }

    std::string Token::toString() const {
        return tokenTypes[type] + lexeme + std::string((const char*)literal);
    }

}
