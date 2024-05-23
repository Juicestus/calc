#include "parser.h"

Expr* Parser::ParseAssignment() {
    LOG(1)
    Token* tk = lex->GetToken();
    if (tk->type != TOK_ID) {
        return ParsePower();
    }
    LOG(2)
    lex->Expect(TOK_ID);
    Lexer* branch = lex->Branch();
    bool assign = branch->Consume(TOK_ASSIGN);
    LOG(3)
    if (!assign) {
        return ParsePower();
    }
    LOG(4)
    std::string name = tk->value;
    lex->Expect(TOK_ASSIGN);
    LOG(5)
    Expr* expr = ParseExpr();
    return new AssignExpr(expr, name);
}

Expr* Parser::ParseAdditive() {
    LOG(1)
    return ParseBinaryOperator({TOK_PLUS, TOK_MINUS}, &Parser::ParseUnaryPrefix);
}

Expr* Parser::ParseMultiplicative() {
    LOG(1)
    return ParseBinaryOperator({TOK_MUL, TOK_DIV}, &Parser::ParseAdditive);
}

Expr* Parser::ParsePower() {
    LOG(1)
    return ParseBinaryOperator({TOK_POWER}, &Parser::ParseMultiplicative);
}

Expr* Parser::ParseUnaryPrefix() {
    Token* op = lex->GetToken();
    if (op->type == TOK_MINUS) {
        lex->Expect(op->type);

        Expr* expr;
        if (lex->GetToken()->type == TOK_LPAREN) {
            LOG(1)
            expr = ParseExpr();
        } else {
            LOG(2)
            expr = ParseNumericLiteral();
        }

        return new UnaryOpExpr(expr, op->type);
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
    return ParseElement();
}

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
    throw new Exception("invalid token", StrFmt("Expected [%s], found [%s]", Token::TypeStr(TOK_ID), tk->TypeStr()), -1, __FILE__, __LINE__);
}

Expr* Parser::ParseExpr() {
    bool grouped = lex->Consume(TOK_LPAREN);
    LOG(1)
    Expr* expr = ParseAssignment();
    LOG(2)
    if (grouped) lex->Expect(TOK_RPAREN);
    return expr;
}

Expr* Parser::ParseBinaryOperator(std::vector<TokenType> tks, Expr* (Parser::*callback)(void)) {
    Expr* left = (*this.*callback)();
    Token* op;
    LOG(1)
    if (VectorContains(tks, (op = lex->GetToken())->type)) {
        lex->Expect(op->type); // cannot fail -- bad practice using this
        LOG(2)
        // Expr* right = (*this.*callback)();
        Expr* right = ParseExpr();
        LOG(3)
        left = new BinOpExpr(left, right, op->type);
    }
    return left;
}