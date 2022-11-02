//#include <vector>
#pragma once

#include <map>
#include <vector>
#include <string.h>

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
     * @brief An Exception class for handling Exceptions during parsing
     * 
     */
    class ParserException : public std::exception {
    private:
        const char* error;

    public:
        ParserException(const char* errorMessage) : error(errorMessage) {
        }

        ParserException() = delete;

        const char* what() const noexcept {
            return this->error;
        }
    };

    /**
     * @brief The lexical scanner of Lox will produce a vector of Tok::Token.
     * 
     */
    class Scanner {
    public:
        const std::string source{};
        std::vector<Tok::Token> tokens{};
    private:
        int start = 0;
        int current = 0;
        int line = 1;

    public: 
        Scanner() = delete;
        Scanner(std::string source);
        std::vector<Tok::Token> scanTokens();
        friend std::ostream& operator<<(std::ostream &os, Scanner &scanner) {
            for (Tok::Token t : scanner.tokens) {
                os << t.toString() << ", ";
                std::flush(os);
            }
            return os << " ###END_TOKEN_LIST###" << std::endl;
        }
    
    private:
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
        //void addToken(Tok::TokenType type, T const* literal);

    };
}