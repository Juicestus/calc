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
    double* var_ptr;

public:
    IdentExpr(const std::string& name);
    ~IdentExpr() = default;

    std::string Str();
    double Eval();
};

class AssignExpr : public Expr {
    std::string name;
    Expr* expr;
    double* var_ptr;

public:
    AssignExpr(Expr* expr, const std::string& name);
    ~AssignExpr() = default;

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

struct Function {
    std::string name;
    std::function<double(std::vector<double>)> callback;
    int n_args;

    Function(const std::string& name, std::function<double(std::vector<double>)> callback, int n_args)
        : name(name), callback(callback), n_args(n_args) {}
};

class FuncCallExpr : public Expr {

private:
    Function* func;
    std::vector<Expr*> args;

public:
    FuncCallExpr(const std::string& name, std::vector<Expr*> args);
    ~FuncCallExpr();

    std::string Str();
    double Eval();
};

class RuntimeManager {
public:

    RuntimeManager(RuntimeManager const&) = delete;
    void operator=(RuntimeManager const&) = delete;

    static RuntimeManager& GetInstance() {
        static RuntimeManager instance;
        return instance;
    }

    Function* ResolveFunction(const std::string& name);
    double* ResolveVar(const std::string& name, bool instantiate_if_missing);

private:
    std::map<std::string, Function*> functions;
    std::map<std::string, double*> variables;
    void AddFunc(const std::string& name, std::function<double(std::vector<double>)> callback, int n_args);

    RuntimeManager();
};

#endif