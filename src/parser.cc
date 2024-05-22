#include "parser.h"

Expr* Parser::Parse(Lexer* lex) {
    


}

Expr* Parser::ParseExpr() {
    return ParseAdditive();
}


Expr* Parser::ParseAdditive() {
    return ParseBinaryOperator({TOK_PLUS, TOK_MINUS}, &Parser::ParseMultiplicative);
}

Expr* Parser::ParseMultiplicative() {
    return ParseBinaryOperator({TOK_MUL, TOK_DIV}, &Parser::ParsePower);
}

Expr* Parser::ParsePower() {
    return ParseBinaryOperator({TOK_POWER}, &Parser::ParseUnaryPrefix);
}

Expr* Parser::ParseUnaryPrefix() {
    Token* op = lex->GetToken();
    if (op->type == TOK_MINUS) {
        lex->Expect(op->type);
        return new UnaryOpExpr(ParseNumericLiteral(), op->type);
    } else {
        return ParseNumericLiteral();
    }
}

Expr* Parser::ParseNumericLiteral() {
    Token* tk = lex->GetToken();
    if (tk->type == TOK_NUM) {
        lex->Expect(tk->type); // cannot fail -- bad practice using this
        return new NumericLiteral(tk->value);
    }
    return ParseIdentifier();
}

Expr* Parser::ParseIdentifier() {
    Token* tk = lex->GetToken();
    if (tk->type == TOK_ID) {
        lex->Expect(tk->type); // cannot fail -- bad practice using this

        if ()


        return new IdentifierExpr(tk->value);
    }
}


Expr* Parser::ParseBinaryOperator(std::vector<TokenType> tks, Expr* (Parser::*callback)(void)) {
    Expr* left = (*this.*callback)();
    Token* op;
    if (VectorContains(tks, (op = lex->GetToken())->type)) {
        lex->Expect(op->type); // cannot fail -- bad practice using this
        // Expr* right = (*this.*callback)();
        Expr* right = ParseExpr();
        left = new BinOpExpr(left, right, op->type);
    }
    return left;
}