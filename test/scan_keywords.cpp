#include <iostream>
#include "scanner.h"

using namespace Tok;

int main()
{
    std::vector<Token> keywords;
    keywords.emplace_back(Token(TokenType::AND, "and", nullptr, 1));
    keywords.emplace_back(Token(TokenType::CLASS, "class", nullptr, 2));
    keywords.emplace_back(Token(TokenType::ELSE, "else", nullptr, 3));
    keywords.emplace_back(Token(TokenType::FALSE, "false", nullptr, 4));
    keywords.emplace_back(Token(TokenType::FOR, "for", nullptr, 5));
    keywords.emplace_back(Token(TokenType::FUN, "fun", nullptr, 6));
    keywords.emplace_back(Token(TokenType::IF, "if", nullptr, 7));
    keywords.emplace_back(Token(TokenType::NIL, "nil", nullptr, 8));
    keywords.emplace_back(Token(TokenType::OR, "or", nullptr, 9));
    keywords.emplace_back(Token(TokenType::PRINT, "print", nullptr, 10));
    keywords.emplace_back(Token(TokenType::RETURN, "return", nullptr, 11));
    keywords.emplace_back(Token(TokenType::SUPER, "super", nullptr, 12));
    keywords.emplace_back(Token(TokenType::THIS, "this", nullptr, 13));
    keywords.emplace_back(Token(TokenType::TRUE, "true", nullptr, 14));
    keywords.emplace_back(Token(TokenType::VAR, "var", nullptr, 15));
    keywords.emplace_back(Token(TokenType::WHILE, "while", nullptr, 16));


    std::cout << "Testing keywords: " << "\n\n";
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