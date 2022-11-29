#include <string>
#include <iostream>
#include <vector>

namespace genAST {
    
    void defineAst(std::string outDir, std::string baseName, std::vector<std::string> types) {

    }

    /**
     * @brief Entry point of the small script that will generate our Expr.cpp file
     */
    int main(int argc, char const *argv[])
    {
        if (argc != 1)
        {
            std::cout << "Usage: generate_ast <output directory>\n";
            std::exit(1);
        }
        std::string outDir = argv[0];

        defineAst(outDir, "Expr", std::vector<std::string>{
            "Binary   : Expr left, Token operator, Expr right",
            "Grouping : Expr expression",
            "Literal  : Object value",
            "Unary    : Token operator, Expr right"
        });

        return 0;
    }
    
}