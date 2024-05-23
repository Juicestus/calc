#ifndef _CALC_PARSER_H_
#define _CALC_PARSER_H_

#include "common.h"
#include "lexer.h"
#include "util/util.h"
#include "ast.h"
#include "token.h"

class Parser { 
public:

    Parser(Lexer* lex) : lex(lex) {}
    Expr* ParseExpr(); 

private: 
    Lexer* lex;

    Expr* ParseAssignment(); 
    Expr* ParseAdditive(); 
    Expr* ParseMultiplicative();
    Expr* ParsePower();
    Expr* ParseUnaryPrefix();
    Expr* ParseNumericLiteral();
    Expr* ParseElement();

    Expr* ParseBinaryOperator(std::vector<TokenType> tks, Expr* (Parser::*callback)(void));
};

#endif