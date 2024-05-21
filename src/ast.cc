#include "ast.h"

NumericLiteral::NumericLiteral(const std::string& value) {
    this->value = std::stod(value);
}

std::string NumericLiteral::Str() {
    return std::to_string(this->value);
}

double NumericLiteral::Eval() {
    return this->value;
}

#define DEF_OP(T, XPR) case T: this->callback = [](double x, double y) -> double { return XPR; }; break;

BinOpExpression::BinOpExpression(Expression* left, Expression* right, TokenType tk_type) {
    this->left = left;
    this->right = right;

    switch (tk_type) {
        DEF_OP('+', x+y)
        DEF_OP('-', x-y)
        DEF_OP('*', x*y)
        DEF_OP('/', x/y)
        DEF_OP('^', std::pow(x, y))
    }
    // this should err out, TODO: add err
}

BinOpExpression::~BinOpExpression() {
    delete this->left;
    delete this->right;
}

std::string BinOpExpression::Str() {
    return "binop";
}

double BinOpExpression::Eval() {
    return this->callback(left->Eval(), right->Eval());
}