#include "main.h"



int main(const int argc, const char** argv) {

    std::cout << "Math solver:\n";
    std::string buff;
    Lexer* lexer;

    double* prev_result_ptr = RuntimeManager::GetInstance().ResolveVar("_", true);

    while (true) {
        std::cout << "> ";
        // std::cin >> buff;
        std::getline(std::cin, buff);

        if (buff == "exit") {
            break;
        }

        // // Log the tokenized expression:
        // lexer = new Lexer(buff);
        // Token* tk;
        // while ((tk = lexer->NextToken())->type != TOK_END) {
        //     std::cout << tk->Str();
        // }
        // std::cout << "\n";

        Parser* parser;
        Expr* expr;

        try {
            lexer = new Lexer(buff);

            lexer->NextToken();
            parser = new Parser(lexer);

            expr = parser->ParseExpr();

        } catch (Exception* e) {
            std::cout << e->Str() << "\n";
            continue;
        }

        // Log the parsed expression:
        // std::cout << expr->Str() << "\n";

        double result = expr->Eval();

        *prev_result_ptr = result;

        std::cout << result << "\n";
    }
}
