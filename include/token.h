#pragma once

#include <vector>

namespace Tok {

    static std::vector<std::string> tokenVals = {
        // Single-character tokens.
        "(", ")", "{", "}", 
        ",", ".", "-", "+", ";", "/", "*",
        
        // One or two character tokens.
        "!", "!=", "=", "==", 
        ">", ">=", "<", "<=",

        // Literals.
        "identifier", "string", "number",

        //Keywords
        "and", "class", "else", "false", "fun", "for", 
        "if", "nil", "or", "print", "return", "super", 
        "this", "true", "var", "while", "EOF"
    };

    enum class TokenType {
        // Single-character tokens. count: 11
        LEFT_PAREN = 0, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // One or two character tokens. count: 8
        BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

        // Literals. count: 3
        IDENTIFIER, STRING, NUMBER,

        // Keywords. count: 17 
        AND, CLASS, ELSE, FALSE, FUN, FOR, 
        IF, NIL, OR, PRINT, RETURN, SUPER, 
        THIS, TRUE, VAR, WHILE, EOF_LOX
    };

    inline std::ostream& operator<<(std::ostream &os, TokenType type) {
        return os << tokenVals[static_cast<int>(type)];
    }

    inline std::string& toString(TokenType type) {
        return tokenVals[static_cast<int>(type)];
    }

    class Token {
    public:
        TokenType type;
        std::string lexeme;
        void* literal;
        int line;

        Token();
        Token(TokenType type, std::string lexeme, void* literal, int line);
        std::string toString() const;
    };
}