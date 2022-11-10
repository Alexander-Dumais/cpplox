#include <iostream>
#include "scanner.h"

int main()
{
    std::string source = "{}==<=>=>< =";

    // std::string source = "{}==<=>=>< //hello\n";
    // std::string source = "{}==<=>=>< //hello";

    // std::string source = "["; //Currently this segmentation faults. Figure out why
    Scan::Scanner scanner(source);
    scanner.scanTokens();

    std::cout << scanner << std::endl;
}