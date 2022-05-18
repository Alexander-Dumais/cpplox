#pragma once

#include <vector>

namespace Tok {

    /**
     * @brief The literal values of the tokens in the Lox Language.
     * 
     *          It's likely better to do away with the separated tokenVals and TokenType definitions, and form
     *          a map like I do with Scan::keywords. 
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
        "identifier", "string", "number",

        //Keywords
        "and", "class", "else", "false", "fun", "for", 
        "if", "nil", "or", "print", "return", "super", 
        "this", "true", "var", "while", "EOF"
    };

    /**
     * @brief The enumerated TokenTypes for the Lox Language.
     * 
     *          These TokenTypes could have been represented by the char type, negating the need for
     *          tokenVals to represent their literals. Doing so would require a different way to represent
     *          Literals and Identifiers. The two character tokens would also cause a problem. There may be
     *          a better solution, but this one works and is fast.
     * 
     */
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

    /**
     * @brief output stream operator definition for Tokens
     * 
     * @param os the output stream
     * @param type the TokenType
     * @return std::ostream& The output stream with the literal for the `type` appended to the buffer.
     */
    inline std::ostream& operator<<(std::ostream &os, TokenType type) {
        return os << tokenVals[static_cast<int>(type)];
    }

    /**
     * @brief TokenType -> std::string function for Tokens 
     * 
     * @param type the TokenType
     * @return std::string The string literal representing the Token based on the `type`
     */
    inline std::string toString(TokenType type) {
        return tokenVals[static_cast<int>(type)];
    }

    /**
     * @brief The Token for Lox which holds the `type` and the string `literal` of a Token.
     * 
     */
    class Token {
    public:
        TokenType type;
        std::string lexeme;
        void* literal;
        int line;

        Token() = delete;
        Token(TokenType type, std::string lexeme, void* literal, int line);
        std::string toString() const;
    };
}