#include <iostream>
#include <algorithm>
#include <tuple>
#include <functional>
#include "scanner.h"

using namespace Tok;

/**
 * @brief returns an upperCase copy of the given string
 * 
 * @param s a string, passed by copy
 * @return std::string s
 */
static inline std::string toUpper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::toupper(c); });
    return s;

}

struct AllTokens
{
    std::vector<Token> *operators, *operators2, *literals, *keywords;
};

AllTokens fillTokenVectors()
{
    std::vector<Token> *operators = new std::vector<Token>;
    std::vector<Token> *operators2 = new std::vector<Token>;
    std::vector<Token> *literals = new std::vector<Token>;
    std::vector<Token> *keywords = new std::vector<Token>;

    operators->reserve(11);
    operators2->reserve(8);
    literals->reserve(3);
    keywords->reserve(17);
    
    // Single character Tokens
    operators->emplace_back(Token(TokenType::LEFT_PAREN, "(", nullptr, 1));
    operators->emplace_back(Token(TokenType::RIGHT_PAREN, ")", nullptr, 2));
    operators->emplace_back(Token(TokenType::LEFT_BRACE, "{", nullptr, 3));
    operators->emplace_back(Token(TokenType::LEFT_BRACE, "}", nullptr, 4));
    operators->emplace_back(Token(TokenType::COMMA, ",", nullptr, 5));
    operators->emplace_back(Token(TokenType::DOT, ".", nullptr, 6));
    operators->emplace_back(Token(TokenType::MINUS, "-", nullptr, 7));
    operators->emplace_back(Token(TokenType::PLUS, "+", nullptr, 8));
    operators->emplace_back(Token(TokenType::SEMICOLON, ";", nullptr, 9));
    operators->emplace_back(Token(TokenType::SLASH, "/", nullptr, 10));
    operators->emplace_back(Token(TokenType::STAR, "*", nullptr, 11));

    // One or two character tokens.
    operators2->emplace_back(Token(TokenType::BANG, "!", nullptr, 12));
    operators2->emplace_back(Token(TokenType::BANG_EQUAL, "!=", nullptr, 13));
    operators2->emplace_back(Token(TokenType::EQUAL, "=", nullptr, 14));
    operators2->emplace_back(Token(TokenType::EQUAL_EQUAL, "==", nullptr, 15));
    operators2->emplace_back(Token(TokenType::GREATER, ">", nullptr, 16));
    operators2->emplace_back(Token(TokenType::GREATER_EQUAL, ">=", nullptr, 17));
    operators2->emplace_back(Token(TokenType::LESS, "<", nullptr, 18));
    operators2->emplace_back(Token(TokenType::LESS_EQUAL, "<=", nullptr, 19));

    // Literal Tokens
    literals->emplace_back(Token(TokenType::IDENTIFIER, "exampleVar", "exampleVar", 20));
    literals->emplace_back(Token(TokenType::STRING, "Hello, World!", "Hello, World!", 21));
    literals->emplace_back(Token(TokenType::NUMBER, "8.0", 8.0, 22));

    // Keyord Tokens
    keywords->emplace_back(Token(TokenType::AND, "and", nullptr, 23));
    keywords->emplace_back(Token(TokenType::CLASS, "class", nullptr, 24));
    keywords->emplace_back(Token(TokenType::ELSE, "else", nullptr, 25));
    keywords->emplace_back(Token(TokenType::FALSE, "false", nullptr, 26));
    keywords->emplace_back(Token(TokenType::FOR, "for", nullptr, 27));
    keywords->emplace_back(Token(TokenType::FUN, "fun", nullptr, 28));
    keywords->emplace_back(Token(TokenType::IF, "if", nullptr, 29));
    keywords->emplace_back(Token(TokenType::NIL, "nil", nullptr, 30));
    keywords->emplace_back(Token(TokenType::OR, "or", nullptr, 31));
    keywords->emplace_back(Token(TokenType::PRINT, "print", nullptr, 32));
    keywords->emplace_back(Token(TokenType::RETURN, "return", nullptr, 33));
    keywords->emplace_back(Token(TokenType::SUPER, "super", nullptr, 34));
    keywords->emplace_back(Token(TokenType::THIS, "this", nullptr, 35));
    keywords->emplace_back(Token(TokenType::TRUE, "true", nullptr, 36));
    keywords->emplace_back(Token(TokenType::VAR, "var", nullptr, 37));
    keywords->emplace_back(Token(TokenType::WHILE, "while", nullptr, 38));
    keywords->emplace_back(Token(TokenType::EOF_LOX, "EOF", nullptr, 39));

    return {operators, operators2, literals, keywords};
}

/**
 * @brief Takes a vector of tokens and tests that they match known tokens.
 * 
 * @param describe Describe the test
 * @param tokens The Token vector
 * @param condition a lambda conditional for matching known tokens
 */
void testVecOfTokens(std::string describe, std::vector<Token> &tokens, bool(*condition)(Token))
{
    std::cout << "\n" << describe << "\n\n";
    std::cout << "lexeme" << "\t-    " << "TYPE" << "\n\n";
    for (auto token : tokens)
    {
        if (condition(token))
            std::cout   << "'" << std::any_cast<std::string>(token.lexeme) << "'" 
                        << "\t-    " << token.type << "\n";    
        else
        {
            std::cout << "ERROR Scanning " << token.toString() << std::endl;
        }
    }
}

/**
 * @brief This test should be run after every major change as a sanity check.
 * 
 * @return int 
 */
int main()
{
    // Initialize vectors of Tokens to test
    AllTokens tokenGroups = fillTokenVectors();

    auto typical_lambda  = [](Token t) {return std::find(tokenVals.begin(), tokenVals.end(), toUpper(t.lexeme)) != tokenVals.end();};
    auto lit_lambda      = [](Token t) {return std::find(tokenVals.begin(), tokenVals.end(), toUpper(toString(t.type))) != tokenVals.end();};

    testVecOfTokens ("Testing Single Character Tokens: ", *tokenGroups.operators, typical_lambda);
    testVecOfTokens ("Testing 1-2 Characters Operators: ", *tokenGroups.operators2, typical_lambda);
    testVecOfTokens ("Testing Literals: ", *tokenGroups.literals, lit_lambda);
    testVecOfTokens ("Testing Keywords: ", *tokenGroups.keywords, typical_lambda);
}