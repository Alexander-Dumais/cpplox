#include <iostream>
#include "scanner.h"

int main() {
    auto tok = Tok::Token(Tok::TokenType::STRING, "Example", (void*)"Example", 1);

    for (auto v : Scan::keywords) {
        std::cout << v.first << ", " << v.second << std::endl;
    }

}