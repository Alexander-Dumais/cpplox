#include <string>
#include <iostream>

#include "token.h"

namespace Tok
{

    Token::Token(const TokenType type, const std::string lexeme, const std::any literal, const int line)
        : type(type), lexeme(lexeme), literal(literal), line(line)
    {
    }

    std::string Token::toString() const
    {
        return toStringType() + ", lexeme: '" + this->lexeme + "', literal: " + litToString();
    }

    std::string Token::toStringType() const
    {
        return Tok::toString(type);
    }

    std::string Token::litToString() const 
    {
        switch (this->type) 
        {
            case TokenType::NUMBER:
                return std::to_string(std::any_cast<double>(this->literal));
            case TokenType::STRING:
                return std::any_cast<std::string>(this->literal);
            //in any other case, just return the lexeme
            default:
                return this->lexeme;

        }
    }
}
