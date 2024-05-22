#include "parser.h"

Expr* Parser::ParseAdditive() {
    return ParseBinaryOperator({TOK_PLUS, TOK_MINUS}, &Parser::ParseMultiplicative);
}

Expr* Parser::ParseMultiplicative() {
    return ParseBinaryOperator({TOK_MUL, TOK_DIV}, &Parser::ParsePower);
}

Expr* Parser::ParsePower() {
    return ParseBinaryOperator({TOK_POWER}, &Parser::ParseAdditive);
}

Expr* Parser::ParseUnaryPrefix() {
    Token* op = lex->GetToken();
    if (op->type == TOK_MINUS) {
        lex->Expect(op->type);
        return new UnaryOpExpr(ParseNumericLiteral(), op->type);
    } else {
        return ParseExpr();
    }
}

Expr* Parser::ParseNumericLiteral() {
    Token* tk = lex->GetToken();
    if (tk->type == TOK_NUM) {
        lex->Expect(tk->type); // cannot fail -- bad practice using this
        return new NumericLiteral(tk->value);
    }
    return ParseElement();
}
/*
 auto elements = new Expressions();
    lex->Match(start);
    if (lex->Tk()->type != end) {
        elements->push_back(ParseExpression());
        while (lex->Consume(',')) {
            elements->push_back(ParseExpression());
        }
    }
    lex->Match(end);
    return elements;*/

Expr* Parser::ParseElement() {
    Token* tk = lex->GetToken();
    if (tk->type == TOK_ID) {
        std::string name = tk->value;

        lex->Expect(tk->type); // cannot fail -- bad practice using this
        tk = lex->GetToken();

        if (tk->type == TOK_LPAREN) {
            lex->Expect(tk->type); // cannot fail -- bad practice using this
            std::vector<Expr*> args;

            if (lex->GetToken()->type != TOK_RPAREN) {
                args.push_back(ParseExpr());
                while (lex->Consume(TOK_COMMA)) {
                    args.push_back(ParseExpr());
                }
            }
            lex->Expect(TOK_RPAREN);

            return new FuncCallExpr(name, args);
        }

        return new IdentExpr(name);
    }
    // wtf is this case? can this happen?
    return new IdentExpr("__undefined__");
}

Expr* Parser::ParseExpr() {
    bool grouped = lex->Consume(TOK_LPAREN);
    Expr* expr = ParseUnaryPrefix();
    if (grouped) lex->Expect(TOK_RPAREN);
    return expr;
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