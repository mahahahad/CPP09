#include "PmergeMe.hpp"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    PmergeMe pmg;

    for (int i = 1; i < argc; i++) {
        if (pmg.handleAdd(argv[i]))
            break ;
    }
    pmg.sort(pmg.getArr());
    pmg.printArr(pmg.getMain());
    return (0);
}
