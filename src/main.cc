#include "main.h"

#include <locale>


int main(const int argc, const char** argv) {

    std::cout << "Math solver:\n";
    std::string buff;
    Lexer* lexer;

    while (true) {
        std::cout << "> ";
        // std::cin >> buff;
        std::getline(std::cin, buff);

        // // Log the tokenized expression:
        // lexer = new Lexer(buff);
        // Token* tk;
        // while ((tk = lexer->NextToken())->type != TOK_END) {
        //     std::cout << tk->Str();
        // }
        // std::cout << "\n";

        lexer = new Lexer(buff);

        lexer->NextToken();
        Parser* parser = new Parser(lexer);

        Expr* expr = parser->ParseExpr();

        // Log the parsed expression:
        std::cout << expr->Str() << "\n";

        std::cout << expr->Eval() << "\n";
    }
}
