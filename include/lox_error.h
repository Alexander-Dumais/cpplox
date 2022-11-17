#pragma once
#include <iostream>

namespace lox_error {
    static bool hadError = false;

    /**
     * @brief report an error to standard out
     *
     * @param line of the error
     * @param where source of error
     * @param message error message
     *
     * TODO: It's possible to have very precise error reports where the exact token causing a parsing problem is identified.
     *       I would like to do this in the near future.
     *
     * ideal example:
     *  Error: Unexpected "," in argument list.
     *
     *   15 | function(first, second,);
     *                              ^-- Here.
     */
    inline void report(int line, std::string where, std::string message)
    {
        std::cout << "[line " << line << "] Error " << where << ": " << message << std::endl;
        hadError = true;
    }

    /**
     * @brief Report an error with the location and a custom message
     *
     * @param line of the error
     * @param message describing the error
     */
    inline void error(int line, std::string message)
    {
        report(line, "", message);
    }
}
