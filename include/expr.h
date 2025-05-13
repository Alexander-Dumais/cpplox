#pragma once
#include "token.h"
#include <any>

namespace Exp{
    class Expr 
    {
    public:
        Expr() = default;
        virtual ~Expr() = 0;
    };

    class Binary : virtual public Expr 
    {
        const Expr &left;
        const Lox::Token &op;
        const Expr &right;

    public:
        Binary() = delete;
        Binary(const Expr &left, const Lox::Token &op, const Expr &right) 
            : left(left), op(op), right(right) {}
        ~Binary()
        {
            delete &left;
            delete &op;
            delete &right;
        }

    };

    class Unary : virtual public Expr
    {
        const Lox::Token &op;
        const Expr &expression;

    public:
        Unary() = delete;
        Unary(const Lox::Token &op, const Expr &expression)
            : op(op), expression(expression) {}
        ~Unary()
        {
            delete &op;
            delete &expression;
        }
    };

    class Literal : virtual public Expr
    {
        const std::any &literal;

    public:
        Literal() = delete;
        Literal(const std::any &literal) 
            : literal(literal){}
        ~Literal()
        {
            delete &literal;
        }

    };

    class Grouping : virtual public Expr
    {
        const Expr &expression;

    public:
        Grouping() = delete;
        Grouping(const Exp::Expr &expression)
            : expression(expression) {}
        ~Grouping()
        {
            delete &expression;
        }
    };
}
