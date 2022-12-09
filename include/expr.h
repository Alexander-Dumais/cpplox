#pragma once
#include "token.h"
#include <any>

namespace Exp{
    class Expr 
    {
    public:
        Expr() = default;
        virtual ~Expr() = default;
    };

    class Binary : public Expr 
    {
        const Expr &left;
        const Tok::Token &op;
        const Expr &right;

    public:
        Binary() = delete;
        Binary(const Expr &left, const Tok::Token &op, const Expr &right) 
            : left(left), op(op), right(right) {}
        ~Binary()
        {
            delete &left;
            delete &op;
            delete &right;
        }

    };

    class Unary : public Expr
    {
        const Tok::Token &op;
        const Expr &expression;

    public:
        Unary() = delete;
        Unary(const Tok::Token &op, const Expr &expression)
            : op(op), expression(expression) {}
        ~Unary()
        {
            delete &op;
            delete &expression;
        }
    };

    class Literal : public Expr
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

    class Grouping : public Expr
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
