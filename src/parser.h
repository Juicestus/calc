#ifndef _CALC_PARSER_H_
#define _CALC_PARSER_H_

#include "common.h"
#include "lexer.h"
#include "util/util.h"
#include "ast.h"
#include "token.h"

class Parser { 
public:
    static Expr* Parse(Lexer* lex);

private: 

    Lexer* lex;

    Parser(Lexer* lex) : lex(lex) {}

    Expr* ParseExpr(); 
    Expr* ParseAdditive(); 
    Expr* ParseMultiplicative();
    Expr* ParsePower();
    Expr* ParseUnaryPrefix();
    Expr* ParseNumericLiteral();
    Expr* ParseFunctionCall();

    Expr* Parser::ParseBinaryOperator(std::vector<TokenType> tks, Expr* (Parser::*callback)(void));
};

#endif