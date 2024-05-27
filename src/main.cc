#include "main.h"

#define TIME_EVAL

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
        double result;

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

#ifdef TIME_EVAL 
        auto begin = std::chrono::steady_clock::now();
#endif
        result = expr->Eval();

        *prev_result_ptr = result;

#ifdef TIME_EVAL
        auto end = std::chrono::steady_clock::now();
#endif

        std::cout << result;
#ifdef TIME_EVAL
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << " (" << elapsed << " ms)";
#endif
        std::cout << "\n";
    }
}
