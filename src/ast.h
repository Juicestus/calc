#ifndef _CALC_AST_H_
#define _CALC_AST_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "token.h"
#include "exception.h"

class Expr {
public:
    virtual std::string Str() = 0;
    virtual double Eval() = 0;
};

class NumericLiteral : public Expr {
    double value;

public:
    NumericLiteral(const std::string& value);
    ~NumericLiteral() = default;

    std::string Str();
    double Eval();
};

class IdentExpr : public Expr {
    std::string name;

public:
    IdentExpr(const std::string& name);
    ~IdentExpr() = default;

    std::string Str();
    double Eval();
};


class BinOpExpr : public Expr {

private:
    std::function<double(double, double)> callback;

public:
    Expr* left;
    Expr* right;
    TokenType tk_type;

    BinOpExpr(Expr* left, Expr* right, TokenType tk_type);
    ~BinOpExpr();

    std::string Str();
    double Eval();
};

class UnaryOpExpr : public Expr {

private:
    std::function<double(double)> callback;

public:
    Expr* exp;
    TokenType tk_type;

    UnaryOpExpr(Expr* exp, TokenType tk_type);
    ~UnaryOpExpr();

    std::string Str();
    double Eval();
};

class FuncCallExpr : public Expr {

private:
    std::function<double(std::vector<double>)> callback;
    std::vector<Expr*> args;
    std::string name;

public:
    FuncCallExpr(const std::string& name, std::vector<Expr*> args);
    ~FuncCallExpr();

    std::string Str();
    double Eval();
};

class FuncManager {
public:

    FuncManager(FuncManager const&) = delete;
    void operator=(FuncManager const&) = delete;

    static FuncManager& GetInstance() {
        static FuncManager instance;
        return instance;
    }

    std::function<double(std::vector<double>)> Resolve(const std::string& name);

private:
    std::map<std::string, std::function<double(std::vector<double>)>> functions;

    FuncManager();
};

#endif