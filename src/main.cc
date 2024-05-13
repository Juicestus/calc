#include "main.h"

int main(const int argc, const char** argv) {
    const std::string version = "pre-" + CurrentDateStr();
    argparse::ArgumentParser args("compiler", version);

    args.add_argument("-r", "--run").help("Execut an input file").default_value("").metavar("FILENAME");

    try {
        args.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << args;
        return 1;
    }

    std::filesystem::path input(args.get<std::string>("-r"));
}
