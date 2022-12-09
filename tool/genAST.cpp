#include <string>
#include <iostream>
#include <fstream>
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
void defineType(std::ofstream& writer, std::string baseName,
                std::string className, std::string parentClass,
                std::string fields)
{
    int len = parentClass.length();
    //scope for TAB and NL
    {
        #define TAB "\t"
        #define NL "\n"

        //Class header
        writer  << TAB << "struct " << className
                << TAB << (len > 0 ? " : " : "")
                << (len > 0 ? parentClass : "") << NL
                << TAB << "{" << NL
                ;

        //fields
        //writer  << TAB << TAB <<

        //constructors and destructors
        writer  << TAB << TAB << className << "() = delete;" << NL
                ;
        writer  << TAB << TAB << className << "(" << fields << ")" << NL
                << TAB << TAB << "{};" << NL
                ;
        writer  << TAB << TAB << "~" << className << "()" << NL
                << TAB << TAB << "{" << NL
                << TAB << TAB << TAB << "delete& left; delete& oper; delete& right;" << NL
                << TAB << TAB << "};" << NL << NL
                ;

        //close class definition
        writer << TAB << "};" << NL;
    }
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
    //Lowercase basename to fit my c++ file naming standard
    toLower(baseName);

    //Open fileWriter with path 
    std::string path = outDir + "/" + baseName + ".h";
    std::ofstream *fileWriter = new std::ofstream(path);

    //Build the file expr.h
    //includes and namespace
    *fileWriter << "//GENERATED FILE: This is a file generated using ./tool/getAST.cpp\n"
                << "#pragma once\n"
                << "#include \"token.h\"\n\n"

                << "namespace Exp{\n"
                ;

    //TODO: Define base Expr virtual function


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

        //TODO: remove debugging code
        // std::cout << "###Classname- " << className << "\n";
        // std::cout << "###parentClass- " << parentClass << "\n";
        // std::cout << "###Fields- " << fields << "\n\n";
        
        defineType(*fileWriter, baseName, className, parentClass, fields);
    }

    //close namespace scope
    *fileWriter << "}" << std::endl;

    //finally close and delete fileWriter
    fileWriter->close();
    delete fileWriter;
}

/**
 * @brief Entry point of the small script that will generate our Expr.cpp file
 */
int main(int argc, char const *argv[])
{
    if (argc != 2) //filename is always first argument of a c++ file
    {
        std::cout << "Usage: generate_ast <output directory>\n";
        std::exit(1);
    }
    std::string outDir = argv[1];

    defineAst(outDir, "Expr", std::vector<std::string>
    {
        "Expr     |  | const Expr& left, const Tok::Token& oper, const Expr& right",
        "Binary   | public Expr | const Expr& left, const Tok::Token& oper, const Expr& right",
        "Unary    | public Expr | const Tok::Token& oper, const Expr& right",
        "Literal  | public Expr | const Literal& value",
        "Grouping | public Expr | const Expr& expression",
    });

    return 0;
}
