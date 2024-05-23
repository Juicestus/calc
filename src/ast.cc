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

IdentExpr::IdentExpr(const std::string& name) {
    this->name = name;

    this->var_ptr = RuntimeManager::GetInstance().ResolveVar(this->name, false);
    if (this->var_ptr == nullptr) {
        throw new Exception("undefined symbol", StrFmt("Variable [%s] is not defined", name.c_str()), -1, __FILE__, __LINE__);
    }
}

std::string IdentExpr::Str() {
    return this->name + "@" + std::to_string((uintptr_t)this->var_ptr) + " )";
}

double IdentExpr::Eval() {
    return *var_ptr;
}

AssignExpr::AssignExpr(Expr* expr, const std::string& name) {
    this->name = name;
    this->expr = expr;

    var_ptr = RuntimeManager::GetInstance().ResolveVar(this->name, true);
    // if (var_ptr == nullptr) {
        // throw new Exception("undefined symbol", StrFmt("Variable [%s] is not defined", name.c_str()), -1, __FILE__, __LINE__);
    // }
}

std::string AssignExpr::Str() {
    return "( " + this->expr->Str() + " -> " + this->name + "@" + std::to_string((uintptr_t)this->var_ptr) + " )";
}

double AssignExpr::Eval() {
    double value = this->expr->Eval();
    *var_ptr = value;
    return value;
}

#define DEF_B_OP(T, XPR) case T: this->callback = [](double x, double y) -> double { return XPR; }; return;

BinOpExpr::BinOpExpr(Expr* left, Expr* right, TokenType tk_type) {
    this->left = left;
    this->right = right;
    this->tk_type = tk_type;

    switch (tk_type) {
        DEF_B_OP(TOK_PLUS, x+y)
        DEF_B_OP(TOK_MINUS, x-y)
        DEF_B_OP(TOK_MUL, x*y)
        DEF_B_OP(TOK_DIV, x/y)
        DEF_B_OP(TOK_POWER, std::pow(x, y))
    }

    throw new Exception("undefined operation", StrFmt("Operator [%s] is not defined", Token::TypeStr(tk_type)), -1, __FILE__, __LINE__);
}

BinOpExpr::~BinOpExpr() {
    delete this->left;
    delete this->right;
}

std::string BinOpExpr::Str() {
    return "( " + left->Str() + " " + Token::TypeStr(tk_type) + " " + right->Str() + " )";
}

double BinOpExpr::Eval() {
    return this->callback(left->Eval(), right->Eval());
}

#define DEF_U_OP(T, XPR) case T: this->callback = [](double x) -> double { return XPR; }; return;

UnaryOpExpr::UnaryOpExpr(Expr* exp, TokenType tk_type) {
    this->exp = exp;
    this->tk_type = tk_type;

    switch (tk_type) {
        DEF_U_OP(TOK_MINUS, -x)
    }
    throw new Exception("undefined operation", StrFmt("Operator [%s] is not defined", Token::TypeStr(tk_type)), -1, __FILE__, __LINE__);
}

UnaryOpExpr::~UnaryOpExpr() {
    delete this->exp;
}

std::string UnaryOpExpr::Str() {
    return Token::TypeStr(tk_type) + exp->Str();
}

double UnaryOpExpr::Eval() {
    return this->callback(exp->Eval());
}

FuncCallExpr::FuncCallExpr(const std::string& name, std::vector<Expr*> args) {
    this->name = name;
    this->args = args;

    auto func_tmp = RuntimeManager::GetInstance().ResolveFunction(name);
    if (func_tmp == nullptr) {
        throw new Exception("undefined symbol", StrFmt("Function [%s] is not defined", name.c_str()), -1, __FILE__, __LINE__);
    }
    this->callback = func_tmp;
}

FuncCallExpr::~FuncCallExpr() {
    for (auto arg : args) {
        delete arg;
    }
}

std::string FuncCallExpr::Str() {
    std::string output = this->name + "( ";
    for (int i = 0; 1; ) {
        output += args[i]->Str();
        if (++i == args.size()) break;
        output += ", ";
    }
    return output + " )";
}

double FuncCallExpr::Eval() {
    std::vector<double> arg_eval;
    for (auto arg : args) {
        arg_eval.push_back(arg->Eval());
    }
    return this->callback(arg_eval);
}

std::function<double(std::vector<double>)> RuntimeManager::ResolveFunction(const std::string& name) {
    if (!functions.count(name)) return nullptr;
    return functions[name];
}

double* RuntimeManager::ResolveVar(const std::string& name, bool instantiate_if_missing) {
    if (!variables.count(name)) {
        if (!instantiate_if_missing) 
            return nullptr;
        variables[name] = new double(0);
    }
    return variables[name];
}

// initialize builtin functions
RuntimeManager::RuntimeManager() {
    functions["sin"] = [](std::vector<double> args)->double { return std::sin(args[0]); };
}