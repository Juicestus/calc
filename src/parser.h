#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include "common.h"
#include "lexer.h"
#include "util/util.h"
#include "ast.h"
#include "token.h"

class Parser { 
public:
    static Expression* Parse(Lexer* lex);

private: 

    Lexer* lex;

    Parser(Lexer* lex) : lex(lex) {}

    Expression* ParseAdditive(void); 
    Expression* ParseAdditive(void); 
    Expression* ParseMultiplicative(void);
    Expression* ParseUnaryExpression(void);
    Expression* ParseNumericLiteral(void);
    Expression* ParseFunctionCall(void);

    Expression* Parser::ParseBinaryOperator(std::vector<TokenType> tks, Expression* (Parser::*callback)(void));
};

#endif