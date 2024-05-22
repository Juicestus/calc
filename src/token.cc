#include "token.h"

TokenType Token::FromChar(char c) {
    switch (c) {
        case '+': return TOK_PLUS;
        case '-': return TOK_MINUS;
        case '*': return TOK_MUL;
        case '/': return TOK_DIV;
        case '(': return TOK_LPAREN;
        case ')': return TOK_RPAREN;
        case ',': return TOK_COMMA;
        case '^': return TOK_POWER;
    }
    return TOK_END;
}

std::string Token::TypeStr(TokenType type) { // static function
    switch (type) {
        case TOK_PLUS: return "+";
        case TOK_MINUS: return "-";
        case TOK_MUL: return "*";
        case TOK_DIV: return "/";
        case TOK_LPAREN: return "(";
        case TOK_RPAREN: return ")";
        case TOK_COMMA: return ",";
        case TOK_POWER: return "^";
        case TOK_END: return "end";
        case TOK_ID: return "id";
        case TOK_NUM: return "num";
    }
    return "?";
}


std::string Token::TypeStr() {
    return TypeStr(this->type); // for instance (method)
}

std::string Token::Str() {
    return "[" + TypeStr() + "]" + value;
}