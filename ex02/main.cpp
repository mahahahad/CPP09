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
    std::cout << "Before: " << pmg.getArr() << std::endl;
    std::cout << "After:  ";
    printArr(pmg.sort(pmg.getArr()));
    std::cout << "Time to process a range of " << pmg.getArr().size() << " elements with std::vector : " << (double)(pmg.endTime - pmg.startTime) * 1000.0 / CLOCKS_PER_SEC << " ms" << std::endl;
    return (0);
}
