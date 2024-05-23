#ifndef _CALC_LEXER_H_
#define _CALC_LEXER_H_

#include "common.h"
#include "token.h"
#include "util/util.h"
#include "exception.h"

class Lexer {

public:
    Lexer(const std::string& expression);
    ~Lexer();

    Lexer* Branch();

    Token* GetToken(); // current token, before next token is processed

    Token* NextToken(); // return next token, advance the iterator

    void Expect(TokenType); // unsafe  --> if the next token isnt whats provided -> crash w/ error
    bool Consume(TokenType); // safe  --> if the next token isnt whats provided -> return false 

private:
    void TokenizeIdentifier(); 
    void TokenizeNumeric();
    void TokenizeElement(); // operators, parens

    int Location();

    char NextChar(); // return previous character and advance the iterator

    char curr_char, next_char;
    char* expression;
    int index, end;
    Token* token;
};


#endif