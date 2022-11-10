#pragma once
#include <variant>

namespace Tok
{
    #define Boolean bool
    #define Number double
    #define String std::string
    #define Nil std::nullptr_t

    using Literal = const std::variant<Boolean, Number, String, Nil>;
}