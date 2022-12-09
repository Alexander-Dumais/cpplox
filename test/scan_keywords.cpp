#include <iostream>
#include "scanner.h"

using namespace Tok;

int main()
{
    //auto tok = Tok::Token(Tok::TokenType::STRING, "Example", "Example", 1);
    std::vector<Token> keywords;
    keywords.emplace_back(Token(TokenType::AND, "and", "and", 1));
    keywords.emplace_back(Token(TokenType::CLASS, "class", "class", 2));
    keywords.emplace_back(Token(TokenType::ELSE, "else", "else", 3));
    keywords.emplace_back(Token(TokenType::FALSE, "false", "false", 4));
    keywords.emplace_back(Token(TokenType::FOR, "for", "for", 5));
    keywords.emplace_back(Token(TokenType::FUN, "fun", "fun", 6));
    keywords.emplace_back(Token(TokenType::IF, "if", "if", 7));
    keywords.emplace_back(Token(TokenType::NIL, "nil", "nil", 8));
    keywords.emplace_back(Token(TokenType::OR, "or", "or", 9));
    keywords.emplace_back(Token(TokenType::PRINT, "print", "print", 10));
    keywords.emplace_back(Token(TokenType::RETURN, "return", "return", 11));
    keywords.emplace_back(Token(TokenType::SUPER, "super", "super", 12));
    keywords.emplace_back(Token(TokenType::THIS, "this", "this", 13));
    keywords.emplace_back(Token(TokenType::TRUE, "true", "true", 14));
    keywords.emplace_back(Token(TokenType::VAR, "var", "var", 15));
    keywords.emplace_back(Token(TokenType::WHILE, "while", "while", 16));


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