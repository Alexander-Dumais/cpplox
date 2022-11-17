#include <iostream>
#include <string>

#include "scanner.h"
#include "debug.h"
#include "lox_error.h"

namespace Scan
{

    /**
     * @brief Scanner constructor
     *
     * @param source The Lox source code
     */
    Scanner::Scanner(std::string source) : source(source) {}

    /**
     * @brief Scans `source` and adds them to `tokens`
     *
     * @return std::vector<Tok::Token> The `tokens` that have been successfully scanned.
     *
     * TODO: Ideally for error handling, this would work like a PEG (Parsing Expression Grammar). It could
     *       Track all the errors, but then contnue to parse the source anyway. This allows the user to
     *       receive all of the parsing errors in bulk, rather than one at a time. This is geat for debugging.
     *       See http://blog.jordan.matelsky.com/365papers/321/ for details on syntax error recovery.
     */
    std::vector<Tok::Token> Scanner::scanTokens()
    {
        while (!isAtEnd())
        {
            start = current;
            scanToken();
        }

        tokens.emplace_back(Tok::TokenType::EOF_LOX, "", nullptr, line);
        return tokens;
    }

    /**
     * @brief Scans for the next token in source
     *
     */
    void Scanner::scanToken()
    {
        char c = advance();
        try
        {
            using namespace Tok;
            switch (c)
            {
                //Single character tokens
                case '(': addToken(TokenType::LEFT_PAREN); break;
                case ')': addToken(TokenType::RIGHT_PAREN); break;
                case '{': addToken(TokenType::LEFT_BRACE); break;
                case '}': addToken(TokenType::RIGHT_BRACE); break;
                case ',': addToken(TokenType::COMMA); break;
                case '.': addToken(TokenType::DOT); break;
                case '-': addToken(TokenType::MINUS); break;
                case '+': addToken(TokenType::PLUS); break;
                case ';': addToken(TokenType::SEMICOLON); break;
                case '*': addToken(TokenType::STAR); break;

                //Two character Tokens
                case '!': addToken(match('=') ? TokenType::BANG_EQUAL       : TokenType::BANG); break;
                case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL      : TokenType::EQUAL); break;
                case '<': addToken(match('=') ? TokenType::LESS_EQUAL       : TokenType::LESS); break;
                case '>': addToken(match('=') ? TokenType::GREATER_EQUAL    : TokenType::GREATER); break;
                
                //comments and whitespace
                //All of these tokens are ignored with the exception of TokenType::SLASH
                case '/':
                    if (match('/')) {
                        //advance until '\n', as thats the scope of a line comment
                        while (peek() != '\n' && !isAtEnd()) advance();
                    } else {
                        addToken(TokenType::SLASH);
                    }
                    break;
                case ' ':
                case '\r':
                case '\t':
                    // Ignore whitespace.
                    break;
                case '\n':
                    line++;
                    break;
                case '"': string(); break;

                default:
                    throw ParserException("Unexpected character", line);
            }
        }
        catch (ParserException const &e)
        {
            DEBUG(std::string("ParserExcepiton -- Scanner::scanToken() | ") + e.what(), std::string(", Line: ") + std::to_string(e.where()));
        }
    }

    void Scanner::string() 
    {
        while (peek() != '"' && !isAtEnd()) 
        {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            lox_error::error(line, "Unterminated string.");
            return;
        }

        // closing the ".
        advance();

        String value = source.substr(start + 1, current - 1);
        addToken(Tok::TokenType::STRING, value);
    }

    void number();
    void identifier();

    /**
     * @brief Match the next character in `source` to the `expected` character
     *
     * @param expected the expected character
     * @return true if the character matched `expected`
     * @return false if the character doesnt match `expected` or if at the end of `source`
     */
    bool Scanner::match(char expected)
    {
        if (isAtEnd())
            return false;
        if (source.at(current) != expected)
            return false;

        current++;
        return true;
    }

    /**
     * @brief Peeks at the current character without advancing; single character lookahead.
     *
     * @return char the current character
     */
    char Scanner::peek()
    {
        if (isAtEnd())
            return '\0';
        return source.at(current);
    }

    char peekNext();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    bool isDigit(char c);

    /**
     * @brief Determines if scanning the `source`    is complete.
     *
     * @return true if the current character location is at or beyond the source length, false otherwise
     */
    bool Scanner::isAtEnd()
    {
        return current >= (int)source.length();
    }

    /**
     * @brief Increment `current` to be the next character in `source` and return the next character
     *
     * @return The next character
     */
    char Scanner::advance()
    {
        return source.at(current++);
    }

    /**
     * @brief addToken with no literal
     *
     * @param type the Token type
     */
    void Scanner::addToken(Tok::TokenType type)
    {
        addToken(type, nullptr);
    }

    /**
     * @brief add a Token to the end of `tokens`
     *
     * @param type The TokenType
     * @param literal The literal of the `type`
     */
    void Scanner::addToken(Tok::TokenType type, Tok::Literal const &literal)
    {
        std::string text = source.substr(start, current);
        tokens.emplace_back(type, text, literal, line);
    }
}