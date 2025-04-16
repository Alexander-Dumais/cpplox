#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "stringUtils.h"

/**
 * @brief writes the class types to a file using the std::ofstream `writer`
 * 
 * @param writer std::ofstream with a set path
 * @param className the string name of the class
 * @param parentClass the parent class, if any
 * @param fields the fields of the class
 */
void defineType(std::ofstream& writer, std::string className, 
    std::string parentClass, std::string fields)
{
    int len = parentClass.length();
    std::stringstream ss(fields);
    std::string sub;
    #define TAB "\t"
    #define NL "\n"

    //Class header
    writer  << TAB "struct " << className
            << (len > 0 ? " : " + parentClass + NL : "")
            << TAB "{" NL
            ;

    while(std::getline(ss, sub, ',')) {
        trim(sub);
        writer << TAB TAB << sub << ";" NL;
    }
    writer << NL;

    //constructors and destructors
    writer  << TAB TAB << className << "() = delete;" NL
            ;
    writer  << TAB TAB << className << "(" << fields << ");" NL
            ;

    //close class definition
    writer << TAB "};" NL NL;
}

/**
 * @brief Generates the data classes necessary for producing the AST
 * 
 * @param outDir the output directory
 * @param baseName the base file name
 * @param types the types for the data classes being generated 
 */
void defineAst(std::string outDir, std::string baseName, std::vector<std::string> types)
{
    #define TAB "\t"
    #define NL "\n"

   //Lowercase basename to fit my c++ file naming standard
    toLower(baseName);

    //Open fileWriter with path 
    std::string path = outDir + "/" + baseName + ".h";
    std::ofstream *fileWriter = new std::ofstream(path);

    //Build the file expr.h
    //includes and namespace
    *fileWriter << "//GENERATED FILE: generated using getAST.cpp" NL
                << "#pragma once" NL
                << "#include \"token.h\"" NL NL

                << "namespace Exp{" NL
                << TAB "struct Expr {};" NL NL
                ;

    //For every class, generate the constructor
    for (std::string type : types)
    {
        int firstDelim = type.find_first_of("|"); //first delimiter location
        int secondDelim = type.find_last_of("|"); //second delimiter location

        std::string className = type.substr(0, firstDelim);
        std::string parentClass = type.substr(firstDelim + 1, secondDelim - firstDelim - 1);
        std::string fields = type.substr(secondDelim + 1, type.length() - secondDelim);
        trim(className);
        trim(parentClass);
        trim(fields);

        defineType(*fileWriter, className, parentClass, fields);
    }

    //close namespace scope
    *fileWriter << "}" << std::endl;

    //finally close and delete fileWriter
    fileWriter->close();
    delete fileWriter;
}

/**
 * @brief Entry point of the small script that will generate our Expr.h file.
 *        Expr.h will contian the class definitions required to build a full 
 *        abstract syntax tree. Generting this header is easier than modifying
 *        the definitions every time we make changes to the language.
 */
int main(int argc, char const *argv[])
{
    if (argc != 2) 
    {
        std::cout << "Usage: generate_ast <output directory>\n";
        std::exit(1);
    }
    std::string outDir = argv[1];

    defineAst(outDir, "Expr", std::vector<std::string>
    {
        "Binary   | public Expr | const Expr left, const Tok::Token oper,"
        "const Expr right",
        "Unary    | public Expr | const Tok::Token oper, const Expr right",
        "Literal  | public Expr | const std::any value",
        "Grouping | public Expr | const Expr expression",
    });

    return 0;
}
