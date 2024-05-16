#include "main.h"

int main(const int argc, const char** argv) {
    std::cout << "Math solver:\n";
    std::string buff;
    Lexer* lexer;
    while (true) {
        std::cout << "> ";
        std::cin >> buff;

        lexer = new Lexer(buff);
        Token* tk;
        while ((tk = lexer->NextToken())->type != TOK_END) {
            std::cout << tk->Str();
        }
        std::cout << "\n";
    }
}
