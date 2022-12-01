#pragma once
#include "token.h"

namespace Exp{
    class Expr 
    {
    protected:
        const Expr &left;
        const Tok::Token &oper;
        const Expr &right;

    public:
        Expr(const Expr& left, const Tok::Token& oper, const Expr& right) : left(left), oper(oper), right(right){};
        virtual ~Expr() = 0;
    };

    struct Binary : virtual public Expr 
    {
        Binary() = delete;
        Binary(const Expr &left, const Tok::Token &oper, const Expr &right) 
            : Expr(left, oper, right) {};
        ~Binary() 
        {
            delete &left;
            delete &oper;
            delete &right;
        };

    };
}
