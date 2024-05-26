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
    return "[" + this->name + " @ " + std::to_string((uintptr_t)this->var_ptr) + "]";
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
    return "( " + this->expr->Str() + " -> [" + this->name + " @ " + std::to_string((uintptr_t)this->var_ptr) + "] )";
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
    this->args = args;
    this->func = RuntimeManager::GetInstance().ResolveFunction(name);
    if (this->func == nullptr) {
        throw new Exception("undefined symbol", StrFmt("Function [%s] is not defined", name.c_str()), -1, __FILE__, __LINE__);
    }
    if (this->func->n_args != args.size()) {
        throw new Exception("argument mismatch", StrFmt("Function [%s] requires %d argument(s), but %d given", 
                this->func->name.c_str(), this->func->n_args, args.size()), -1, __FILE__, __LINE__);
    }
}

FuncCallExpr::~FuncCallExpr() {
    for (auto arg : args) {
        delete arg;
    }
}

std::string FuncCallExpr::Str() {
    std::string output = this->func->name + "( ";
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
    return this->func->callback(arg_eval);
}

Function* RuntimeManager::ResolveFunction(const std::string& name) {
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


void RuntimeManager::AddFunc(const std::string& name, std::function<double(std::vector<double>)> callback, int n_args) {
    if (functions.count(name)) {
        throw new Exception("redefinition", StrFmt("Function [%s] is already defined", name.c_str()), -1, __FILE__, __LINE__);
    }
    functions[name] = new Function(name, callback, n_args);
}



// #define DEF_B_FUNC(N, XPR) functions[N] = [](std::vector<double> args)->double { return XPR; };
#define DEF_B_FUNC(L, N, XPR) AddFunc(N, [](std::vector<double> args)->double { return XPR; }, L);

// initialize builtin functions
RuntimeManager::RuntimeManager() {
    *ResolveVar("pi", true) = 3.141592653589793115997963468544185161590576171875; // float64 accurate
    *ResolveVar("e", true) =  2.718281828459045235360287471352662497757247093700; // float64 accurate? (...699->700)

    DEF_B_FUNC( 1, "abs", std::abs(args[0]) )
    DEF_B_FUNC( 1, "sqrt", std::sqrt(args[0]) )
    DEF_B_FUNC( 1, "ln", std::log(args[0]) )
    DEF_B_FUNC( 2, "log", std::log(args[0]) / std::log(args[1]) )
    DEF_B_FUNC( 1, "exp", std::exp(args[0]) )
    DEF_B_FUNC( 1, "floor", std::floor(args[0]) )
    DEF_B_FUNC( 1, "ceil", std::ceil(args[0]) )
    DEF_B_FUNC( 1, "round", std::round(args[0]) )
    DEF_B_FUNC( 2, "min", std::min(args[0], args[1]) )
    DEF_B_FUNC( 2, "max", std::max(args[0], args[1]) )
    DEF_B_FUNC( 2, "fmod", std::fmod(args[0], args[1]) )
    DEF_B_FUNC( 1, "sin", std::sin(args[0]) )
    DEF_B_FUNC( 1, "cos", std::cos(args[0]) )
    DEF_B_FUNC( 1, "tan", std::tan(args[0]) )
    DEF_B_FUNC( 1, "asin", std::asin(args[0]) )
    DEF_B_FUNC( 1, "acos", std::acos(args[0]) )
    DEF_B_FUNC( 1, "atan", std::atan(args[0]) )
    DEF_B_FUNC( 1, "sinh", std::sinh(args[0]) )
    DEF_B_FUNC( 1, "cosh", std::cosh(args[0]) )
    DEF_B_FUNC( 1, "tanh", std::tanh(args[0]) )
    DEF_B_FUNC( 2, "hypot2", std::hypot(args[0], args[1]) )
    DEF_B_FUNC( 3, "hypot3", std::hypot(args[0], args[1], args[2]) )
}