#include <string>
#include <iostream>

#include "token.h"

namespace Tok {

    Token::Token(TokenType type, std::string lexeme, void* literal, int line) 
        : type(type), lexeme(lexeme), literal(literal), line(line)
    {
        std::cout << "Created Token with non-empty constructor" << std::endl;
        std::cout << this->toString() << std::endl;
    }

    std::string Token::toString() const {
        return Tok::toString(type) + lexeme + std::string((const char*)literal);
    }
}
