#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

const std::vector<std::string> tokenTypes = {
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "LEFT_BRACE",
    "RIGHT_BRACE",
    "COMMA",
    "DOT",
    "MINUS",
    "PLUS",
    "SEMICOLON",
    "SLASH",
    "STAR",
    "BANG",
    "BANG_EQUAL",
    "EQUAL",
    "EQUAL_EQUAL",
    "GREATER",
    "GREATER_EQUAL",
    "LESS",
    "LESS_EQUAL",
    "IDENTIFIER",
    "STRING",
    "NUMBER",
    "AND",
    "CLASS",
    "ELSE",
    "FALSE",
    "FUN",
    "FOR",
    "IF",
    "NIL",
    "OR",
    "PRINT",
    "RETURN",
    "SUPER",
    "THIS",
    "TRUE",
    "VAR",
    "WHILE",
    "EOF_LOX" //39 tokens
};

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOF_LOX
};

class Token {
public:
    TokenType type; 
    std::string lexeme;
    void* literal;
    int line;

    Token() {
        //assert(tokenTypes.size() != (int)TokenType(EOF_LOX)); //If this fails, it means the number of tokens does not match the number of TokenTypes
        std::cout << "Created tmpty Token" << std::endl;
    }

    Token(TokenType type, std::string lexeme, void* literal, int line) 
        : type(type), lexeme(lexeme), literal(literal), line(line)
    {
        assert(tokenTypes.size() == 39);

    }

    std::string toString() const {
        //return type + " " + lexeme + " " + literal;
        return tokenTypes[type] + lexeme + std::string((const char*)literal);
    }

};