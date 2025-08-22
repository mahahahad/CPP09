#include "RPN.hpp"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    RPN rpn;

    for (int i = 1; i < argc; i++) {
        if (rpn.handleAdd(argv[i]))
            break ;
    }
    return (rpn.printResult());
}
