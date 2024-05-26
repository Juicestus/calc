#ifndef _CALC_TOKEN_H_
#define _CALC_TOKEN_H_

#include "common.h"
#include "util/util.h"

enum TokenType {
    TOK_END = 0, // EOL

    TOK_ID = 256,

    TOK_NUM,

    TOK_PLUS,
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_COMMA,
    TOK_POWER,
    
    TOK_ASSIGN,
    TOK_MOD,
};

class Token {
public:

    TokenType type;
    int index;
    std::string value;

    Token(TokenType type, int index, const std::string& value) : type(type), index(index), value(value) {}
    ~Token() = default;

    static std::string TypeStr(TokenType type);
    std::string TypeStr();
    std::string Str();

    static TokenType FromChar(char);
};

#endif