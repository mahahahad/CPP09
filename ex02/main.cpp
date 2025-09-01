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
    std::cout << "Before: " << pmg.getVector() << std::endl;
    std::cout << "After:  ";
    printArr(pmg.sort(pmg.getVector()));
    std::cout << "Time to process a range of " << pmg.getVector().size() << " elements with std::vector : " << (double)(pmg.endTime - pmg.startTime) * 1000.0 / CLOCKS_PER_SEC << " ms" << std::endl;
    pmg.sort(pmg.getDeque());
    std::cout << "Time to process a range of " << pmg.getDeque().size() << " elements with std::deque : " << (double)(pmg.endTime - pmg.startTime) * 1000.0 / CLOCKS_PER_SEC << " ms" << std::endl;
    return (0);
}
