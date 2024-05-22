#include "lexer.h"

Lexer::Lexer(const std::string& expression) {

    this->expression = _strdup(expression.c_str());
    this->end = strlen(this->expression);

    // fill current char and next char
    NextChar();
    NextChar();
}

Lexer::~Lexer() {
    free((void*)this->expression); // explicilty free this memory
}

// Some getters, TODO: inline?
int Lexer::Location() { return index; } //ifnoref remove
Token* Lexer::GetToken() { return token; }

// return prev, iter
char Lexer::NextChar() {
    char last = curr_char;
    curr_char = next_char;
    next_char = index < end ? expression[index] : TOK_END;
    index++;
    return last;
}

Token* Lexer::NextToken() {
    token = new Token(TOK_END, 0, "");  

    while (curr_char && IsWhitespace(curr_char)) {
        NextChar();
    }

    token->index = index;

    if (IsAlpha(curr_char)) {
        TokenizeIdentifier();   
    } else if (IsNumeric(curr_char)) {
        TokenizeNumeric();
    } else {
        TokenizeElement();
    }

    return token;
}

void Lexer::TokenizeIdentifier() {
    token->type = TOK_ID;
    while (IsAlpha(curr_char) || IsNumeric(curr_char)) {
        token->value += NextChar();
    }
}

void Lexer::TokenizeNumeric() {
    token->type = TOK_NUM;
    // TODO: add hex?
    while (IsNumeric(curr_char)) {
        token->value += NextChar();
    }
    if (curr_char == '.') { // if not hex
        token->value += NextChar();
        while (IsNumeric(curr_char)) {
            token->value += NextChar();
        }
    }
    if (curr_char == 'e' || curr_char == 'E') { // if not hex
        token->value += NextChar();
        if (curr_char == '-') {
            token->value += NextChar();
        }
        while (IsNumeric(curr_char)) {
            token->value += NextChar();
        }
    }
}

void Lexer::TokenizeElement() {
    token->type = Token::FromChar(curr_char);
    token->value = NextChar();
    // is this func done?
}

bool Lexer::Consume(TokenType tk) {
    if (token->type == tk) {
        NextToken();
        return true;
    }
    return false;
}

void Lexer::Expect(TokenType tk) {
    if (!Consume(tk)) {
        ErrFmt("Error: invalid token, expected [%s], found [%s]. (Lexer::Expect)", Token::TypeStr(tk), token->TypeStr());
    }
}