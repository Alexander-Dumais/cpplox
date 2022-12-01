#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//ltrim and rtrim taken from:
//https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
};

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
};

static inline void trim(std::string & s)
{
    ltrim(s);
    rtrim(s);
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
    std::transform(baseName.begin(), baseName.end(), baseName.begin(),
    [](unsigned char c){ return std::tolower(c); });

    //Open fileWriter with path 
    std::string path = outDir + "/" + baseName + ".h";
    std::cout << path << "\n";
    std::ofstream fileWriter(path);

    //Build the file expr.h
    //includes and namespace
    fileWriter  << "#pragma once\n"
                << "#include \"token.h\"\n\n"

                << "namespace Exp{\n"
                ;

    //For every class, generate the constructor
    for (std::string type : types)
    {
        int firstDelim = type.find_first_of("|"); //first delimiter location
        int secondDelim = type.find_last_of("|"); //second delimiter location

        std::string className = type.substr(0, firstDelim);
        trim(className);
        //std::cout << "###Classname- " << className << "\n";

        std::string parentClass = type.substr(firstDelim + 1, secondDelim - firstDelim - 1);
        trim(parentClass);
        //std::cout << "###parentClass- " << parentClass << "\n";
        
        std::string fields = type.substr(secondDelim + 1, type.length() - secondDelim);
        trim(fields);
        //std::cout << "###Fields- " << fields << "\n\n";

    }

    //close namespace scope
    fileWriter << "}" << std::endl;

    //finally close fileWriter
    fileWriter.close();
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
        "Binary   | public virtial Expr | const Expr& left, const Tok::Token& oper, const Expr& right",
        "Grouping | public virtual Expr | const Expr& expression",
        "Literal  | public virtual Expr | const Literal& value",
        "Unary    | public virtual Expr | const Tok::Token& oper, const Expr& right"
    });

    return 0;
}
