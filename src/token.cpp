#include <string>
#include <iostream>

#include "token.h"

namespace Tok
{

    Token::Token(TokenType type, std::string lexeme, Literal const * literal, int line)
        : type(type), lexeme(lexeme), literal(literal), line(line)
    {
    }

    std::string Token::toString() const
    {
        return Tok::toString(type);
    }
}
