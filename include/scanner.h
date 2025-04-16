//#include <vector>
#pragma once

#include <map>
#include <vector>
#include <iterator>

#include "token.h"

namespace Scan
{
    /**
     * @brief The keywords literals of the Lox language, and their associated TokenTypes.
     *
     */
    static const std::map<std::string, Tok::TokenType> keywords = {
        {"and",     Tok::TokenType::AND},
        {"class",   Tok::TokenType::CLASS},
        {"else",    Tok::TokenType::ELSE},
        {"false",   Tok::TokenType::FALSE},
        {"for",     Tok::TokenType::FOR},
        {"fun",     Tok::TokenType::FUN},
        {"if",      Tok::TokenType::IF},
        {"nil",     Tok::TokenType::NIL},
        {"or",      Tok::TokenType::OR},
        {"print",   Tok::TokenType::PRINT},
        {"return",  Tok::TokenType::RETURN},
        {"super",   Tok::TokenType::SUPER},
        {"this",    Tok::TokenType::THIS},
        {"true",    Tok::TokenType::TRUE},
        {"var",     Tok::TokenType::VAR},
        {"while",   Tok::TokenType::WHILE}};

    /**
     * @brief An Exception class for handling Exceptions during parsing
     *
     */
    class ParserException : public std::exception
    {
    private:
        const char *error;
        int line;

    public:
        ParserException(const char *errorMessage, int lineNumber)
            : error(errorMessage), line(lineNumber)
        {
        }

        ParserException() = delete;

        const char *what() const noexcept
        {
            return this->error;
        }

        const int where() const noexcept
        {
            return this->line;
        }
    };

    /**
     * @brief The lexical scanner of Lox will produce a vector of Tok::Token.
     *
     */
    class Scanner
    {
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
        friend std::ostream &operator<<(std::ostream &os, Scanner &scanner)
        {
            //using iterator to avoid trailing comma
            for (auto it = std::begin(scanner.tokens); it != std::end(scanner.tokens); ++it)
            {
                if (it != scanner.tokens.begin())
                    os << ", ";
                os << it->toStringLit();
            }
            return os;
        }

    private:
        void scanToken();
        void string();
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
        void addToken(Tok::TokenType type, std::any const &literal);

        // template<typename T>  //Example of possible templated solution for accepting multiple literals, instead of void*
        // void addToken(Tok::TokenType type, T const* literal);
    };
}
