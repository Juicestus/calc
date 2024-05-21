#ifndef _CALC_AST_H_
#define _CALC_AST_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "token.h"

class Expression {
public:
    virtual std::string Str() = 0;
    virtual double Eval() = 0;
};

class NumericLiteral : public Expression {
    double value;

public:
    NumericLiteral(const std::string& value);

    std::string Str();
    double Eval();
};



class BinOpExpression : public Expression {

private:
    std::function<double(double, double)> callback;

public:
    Expression* left;
    Expression* right;

    BinOpExpression(Expression* left, Expression* right, TokenType tk_type);

    std::string Str();
    double Eval();
};

#endif