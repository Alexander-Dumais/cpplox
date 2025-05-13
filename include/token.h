#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include <any>

#include "tokentype.h"

namespace Lox
{

    /**
     * @brief The literal values of the tokens in the Lox Language.
     *
     *          It's likely better to do away with the separated tokenVals and TokenType definitions, and form
     *          a map like I do with Lox::keywords.
     *
     */
    static const std::vector<std::string> tokenVals = {
        // Single-character tokens.
        "(", ")", "{", "}",
        ",", ".", "-", "+", ";", "/", "*",

        // One or two character tokens.
        "!", "!=", "=", "==",
        ">", ">=", "<", "<=",

        // Literals.
        "IDENTIFIER", "STRING", "NUMBER",

        // KEYWORDS
        "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR",
        "IF", "NIL", "OR", "PRINT", "RETURN", "SUPER",
        "THIS", "TRUE", "VAR", "WHILE", "EOF"
        };

    /**
     * @brief output stream operator definition for Tokens
     *
     * @param os the output stream
     * @param type the TokenType
     * @return std::ostream& The output stream with the literal for the `type` appended to the buffer.
     */
    inline std::ostream &operator<<(std::ostream &os, TokenType type)
    {
        return os << tokenVals[static_cast<int>(type)];
    }

    /**
     * @brief TokenType -> std::string function for Tokens
     *
     * @param type the TokenType
     * @return std::string The string literal representing the Token based on the `type`
     */
    inline std::string toString(TokenType type) 
    {
        return tokenVals[static_cast<int>(type)];
    }

    /**
     * @brief The Token for Lox which holds the `type` and the string `literal` of a Token.
     *
     */
    class Token
    {
    public:
        const TokenType type;
        const std::string lexeme;
        const std::any literal;
        const int line;

        Token() = delete;
        Token(const TokenType type, const std::string lexeme, const std::any literal, const int line);
        std::string toStringType() const;
        std::string toStringLit() const;
        std::string toString() const;
    };
}
