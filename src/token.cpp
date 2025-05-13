#include <string>
#include <iostream>

#include "token.h"

namespace Lox
{

    Token::Token(const TokenType type, const std::string lexeme, const std::any literal, const int line)
        : type(type), lexeme(lexeme), literal(literal), line(line)
    {
    }

    std::string Token::toString() const
    {
        return toStringType() + ", lexeme: '" + this->lexeme + "', literal: " + toStringLit();
    }

    std::string Token::toStringType() const
    {
        return Lox::toString(type);
    }

    std::string Token::toStringLit() const 
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
