#pragma once

namespace Tok 
{
    /**
     * @brief The enumerated TokenTypes for the Lox Language.
     *
     *          These TokenTypes could have been represented by the char type, negating the need for
     *          tokenVals to represent their literals. Doing so would require a different way to represent
     *          Literals and Identifiers. The two character tokens would also cause a problem. There may be
     *          a better solution, but this one works and is fast.
     *
     */
    enum class TokenType 
    {
        // Single-character tokens. count: 11
        LEFT_PAREN = 0,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        MINUS,
        PLUS,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character tokens. count: 8
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // Literals. count: 3
        IDENTIFIER,
        STRING,
        NUMBER,

        // Keywords. count: 17
        AND,
        CLASS,
        ELSE,
        FALSE,
        FUN,
        FOR,
        IF,
        NIL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,
        EOF_LOX
    };
}