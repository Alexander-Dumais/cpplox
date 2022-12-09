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

        tokens.emplace_back(Tok::TokenType::EOF_LOX, "EOF", nullptr, line);
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
                case '"': 
                    string();
                    break;

                default:
                    if (isDigit(c)) {
                        number();
                    }
                    else if (isAlpha(c))
                    {
                        identifier();
                    }
                    else
                    {
                        throw ParserException("Unexpected character", line);
                    }
                    break;
            }
        }
        catch (ParserException const &e)
        {
            DEBUG(std::string("ParserExcepiton -- Scanner::scanToken() | ") + e.what(), std::string(", Line: ") + std::to_string(e.where()));
        }
    }

    /**
     * @brief Scan for the contents of the string
     * 
     * The contents of the string are saved and added as a token.
     * If the end of the file is reached before the closing '"' is found, throw an error.
     * 
     */
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

        // closing the '"'.
        advance();

        //trim surrounding quotes
        const std::string value = source.substr(start + 1, current - start);
        addToken(Tok::TokenType::STRING, value);
    }

    /**
     * @brief Scan the full number
     * 
     */
    void Scanner::number()
    {
        while (isDigit(peek())) advance();

        //Look for fractional part
        if (peek() == '.' && isDigit(peekNext())) {
            //consume '.'
            advance();

            while (isDigit(peek())) advance();
        }

        const double value = std::stod( source.substr(start, current - start) );
        addToken(Tok::TokenType::NUMBER, value);
    }

    void Scanner::identifier()
    {       
        while(isAlphaNumeric(peek()))
            advance();

        const std::string value = source.substr(start, current - start);
        Tok::TokenType typ;

        if (Scan::keywords.find(value) != Scan::keywords.end())
        {
            //value in keywords, so it's a specific keyword
            typ = Scan::keywords.at(value); 
        }
        else 
        {
            //value not in keywords, so it's an IDENTIFIER
            typ = Tok::TokenType::IDENTIFIER;
        }
        addToken(typ);
    }

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

    /**
     * @brief Peeks the next character without advancing; two character lookahead
     * 
     * @return char the next character
     */
    char Scanner::peekNext() {
        if (current + 1 >= (int)source.length()) 
            return '\0';
        return source.at(current + 1);
    }

    /**
     * @brief Is the character an alphabet character, or an underscore
     * 
     * @param c the char being checked
     * @return true if `c` is a lower case character, upper case character, 
     *          or '_', false otherwise.
     */
    bool Scanner::isAlpha(char c) {
        return  (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                c == '_';        
    }

    /**
     * @brief Is the character an alphabet character, an underscore or a digit
     * 
     * @param c the character being checked
     * @return true if `c` is alpha numeric, false otherwise
     */
    bool Scanner::isAlphaNumeric(char c) {
        return (isAlpha(c) || isDigit(c));
    }

    /**
     * @brief is the character a digit?
     * 
     * @param c, a char
     * @return true if the character `c` is between 0 and 9, false otherwise
     */
    bool Scanner::isDigit(char c)
    {
        return (c >= '0' && c <= '9');
    }

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
    void Scanner::addToken(Tok::TokenType type, std::any const &literal)
    {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, literal, line);
    }
}