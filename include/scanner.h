//#include <vector>
#pragma once

#include <map>
#include <vector>
#include <iterator>

#include "token.h"

namespace Lox
{
    /**
     * @brief The keywords literals of the Lox language, and their associated TokenTypes.
     *
     */
    static const std::map<std::string, Lox::TokenType> keywords = {
        {"and",     Lox::TokenType::AND},
        {"class",   Lox::TokenType::CLASS},
        {"else",    Lox::TokenType::ELSE},
        {"false",   Lox::TokenType::FALSE},
        {"for",     Lox::TokenType::FOR},
        {"fun",     Lox::TokenType::FUN},
        {"if",      Lox::TokenType::IF},
        {"nil",     Lox::TokenType::NIL},
        {"or",      Lox::TokenType::OR},
        {"print",   Lox::TokenType::PRINT},
        {"return",  Lox::TokenType::RETURN},
        {"super",   Lox::TokenType::SUPER},
        {"this",    Lox::TokenType::THIS},
        {"true",    Lox::TokenType::TRUE},
        {"var",     Lox::TokenType::VAR},
        {"while",   Lox::TokenType::WHILE}};

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

        int where() const noexcept
        {
            return this->line;
        }
    };

    /**
     * @brief The lexical scanner of Lox will produce a vector of Lox::Token.
     *
     */
    class Scanner
    {
    public:
        const std::string source{};
        std::vector<Lox::Token> tokens{};

    private:
        int start = 0;
        int current = 0;
        int line = 1;

    public:
        Scanner() = delete;
        Scanner(std::string source);
        std::vector<Lox::Token> scanTokens();
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
        void addToken(Lox::TokenType type);
        void addToken(Lox::TokenType type, std::any const &literal);

        // template<typename T>  //Example of possible templated solution for accepting multiple literals, instead of void*
        // void addToken(Lox::TokenType type, T const* literal);
    };
}
