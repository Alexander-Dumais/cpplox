#include <iostream>
#include "scanner.h"

using namespace Tok;
/*
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
*/

int main()
{
    // Single character tokens
    std::vector<Token> operators;
    operators.emplace_back(Token(TokenType::LEFT_PAREN, "(", nullptr, 1));
    operators.emplace_back(Token(TokenType::RIGHT_PAREN, ")", nullptr, 2));
    operators.emplace_back(Token(TokenType::LEFT_BRACE, "{", nullptr, 3));
    operators.emplace_back(Token(TokenType::LEFT_BRACE, "}", nullptr, 4));
    operators.emplace_back(Token(TokenType::COMMA, ",", nullptr, 5));
    operators.emplace_back(Token(TokenType::DOT, ".", nullptr, 6));
    operators.emplace_back(Token(TokenType::MINUS, "-", nullptr, 7));
    operators.emplace_back(Token(TokenType::PLUS, "+", nullptr, 8));
    operators.emplace_back(Token(TokenType::SEMICOLON, ";", nullptr, 9));
    operators.emplace_back(Token(TokenType::SLASH, "/", nullptr, 10));
    operators.emplace_back(Token(TokenType::STAR, "*", nullptr, 11));
    
    // One or two character tokens.
    std::vector<Token> operators2;
    operators2.emplace_back(Token(TokenType::BANG, "!", nullptr, 12));
    operators2.emplace_back(Token(TokenType::BANG_EQUAL, "!=", nullptr, 13));
    operators2.emplace_back(Token(TokenType::EQUAL, "=", nullptr, 14));
    operators2.emplace_back(Token(TokenType::EQUAL_EQUAL, "==", nullptr, 15));
    operators2.emplace_back(Token(TokenType::GREATER, ">", nullptr, 16));
    operators2.emplace_back(Token(TokenType::GREATER_EQUAL, ">=", nullptr, 17));
    operators2.emplace_back(Token(TokenType::LESS, "<", nullptr, 18));
    operators2.emplace_back(Token(TokenType::LESS_EQUAL, "<=", nullptr, 19));

    // Literal TOkens
    std::vector<Token> literals;
    literals.emplace_back(Token(TokenType::IDENTIFIER, "exampleVar", "exampleVar", 20));
    literals.emplace_back(Token(TokenType::STRING, "Hello, World!", "Hello, World!", 21));
    literals.emplace_back(Token(TokenType::NUMBER, "8.0", 8.0, 22));

    // Keyord Tokens
    std::vector<Token> keywords;
    keywords.emplace_back(Token(TokenType::AND, "and", nullptr, 23));
    keywords.emplace_back(Token(TokenType::CLASS, "class", nullptr, 24));
    keywords.emplace_back(Token(TokenType::ELSE, "else", nullptr, 25));
    keywords.emplace_back(Token(TokenType::FALSE, "false", nullptr, 26));
    keywords.emplace_back(Token(TokenType::FOR, "for", nullptr, 27));
    keywords.emplace_back(Token(TokenType::FUN, "fun", nullptr, 28));
    keywords.emplace_back(Token(TokenType::IF, "if", nullptr, 29));
    keywords.emplace_back(Token(TokenType::NIL, "nil", nullptr, 30));
    keywords.emplace_back(Token(TokenType::OR, "or", nullptr, 31));
    keywords.emplace_back(Token(TokenType::PRINT, "print", nullptr, 32));
    keywords.emplace_back(Token(TokenType::RETURN, "return", nullptr, 33));
    keywords.emplace_back(Token(TokenType::SUPER, "super", nullptr, 34));
    keywords.emplace_back(Token(TokenType::THIS, "this", nullptr, 35));
    keywords.emplace_back(Token(TokenType::TRUE, "true", nullptr, 36));
    keywords.emplace_back(Token(TokenType::VAR, "var", nullptr, 37));
    keywords.emplace_back(Token(TokenType::WHILE, "while", nullptr, 38));
    keywords.emplace_back(Token(TokenType::EOF_LOX, "\0", nullptr, 39));

    //Testing single charatcer tokens
    std::cout << "Testing single character tokens: " << "\n\n";
    std::cout << "lexeme" << "\t-    " << "TYPE" << "\n\n";
    for (auto o : operators)
    {
        if (Scan::keywords.find(o.lexeme) != Scan::keywords.end())
            std::cout << std::any_cast<std::string>(o.lexeme) << "\t-    " << o.type << "\n";    
        else
        {
            std::cout << "ERROR Scanning " << o.toString() << std::endl;
        }
    }

    //Testing 1-2 charscter tokens
    std::cout << "\nTesting 1-2 character tokens: " << "\n\n";
    std::cout << "lexeme" << "\t-    " << "TYPE" << "\n\n";
    for (auto o : operators2)
    {
        if (Scan::keywords.find(o.lexeme) != Scan::keywords.end())
            std::cout << std::any_cast<std::string>(o.lexeme) << "\t-    " << o.type << "\n";    
        else
        {
            std::cout << "ERROR Scanning " << o.toString() << std::endl;
        }
    }

    //Testing literals
    std::cout << "\nTesting literals: " << "\n\n";
    std::cout << "lexeme" << "\t-    " << "TYPE" << "\n\n";
    for (auto l : literals)
    {
        if (Scan::keywords.find(l.lexeme) != Scan::keywords.end())
            std::cout << std::any_cast<std::string>(l.lexeme) << "\t-    " << l.type << "\n";    
        else
        {
            std::cout << "ERROR Scanning " << l.toString() << std::endl;
        }
    }

    //testing keywords
    std::cout << "\nTesting keywords: " << "\n\n";
    std::cout << "lexeme" << "\t-    " << "TYPE" << "\n\n";
    for (auto k : keywords)
    {
        if (Scan::keywords.find(k.lexeme) != Scan::keywords.end())
            std::cout << std::any_cast<std::string>(k.lexeme) << "\t-    " << k.type << "\n";    
        else
        {
            std::cout << "ERROR Scanning " << k.toString() << std::endl;
        }
    }
}