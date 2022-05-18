//#include <vector>
#pragma once

#include <map>
#include <vector>

#include "token.h"

namespace Scan
{
    /**
     * @brief The keywords literals of the Lox language, and their associated TypenTypes.
     * 
     */
    static const std::map<std::string, Tok::TokenType> keywords = {
        {"and",    Tok::TokenType::AND},
        {"class",  Tok::TokenType::CLASS},
        {"else",   Tok::TokenType::ELSE},
        {"false",  Tok::TokenType::FALSE},
        {"for",    Tok::TokenType::FOR},
        {"fun",    Tok::TokenType::FUN},
        {"if",     Tok::TokenType::IF},
        {"nil",    Tok::TokenType::NIL},
        {"or",     Tok::TokenType::OR},
        {"print",  Tok::TokenType::PRINT},
        {"return", Tok::TokenType::RETURN},
        {"super",  Tok::TokenType::SUPER},
        {"this",   Tok::TokenType::THIS},
        {"true",   Tok::TokenType::TRUE},
        {"var",    Tok::TokenType::VAR},
        {"while",  Tok::TokenType::WHILE}
    };

    /**
     * @brief The lexical scanner of Lox will produce a vector of Tok::Token.
     * 
     */
    class Scanner {
        const std::string source;
        std::vector<Tok::Token> tokens;
        int start = 0;
        int current = 0;
        int line = 1;

        Scanner() = delete;
        Scanner(std::string source);

        std::vector<Tok::Token> scanTokens();
        void scanToken();
        void number();
        void identifier();
        bool match(char expected);
        char peek();
        char peekNext();
        bool isAlpha(char c);
        bool isAlphaNumeric(char c);
        bool isDigit(char c);
        bool isAtEnd();
        char advance();
        void addToken(Tok::TokenType type);
        void addToken(Tok::TokenType type, void* literal);
        
        //template<typename T>  //Example of possible templated solution for accepting multiple literals, instead of void*
        //void addToken(Tok::TokenType type, int const* literal);

    };

}