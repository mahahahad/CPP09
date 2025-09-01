#include "PmergeMe.hpp"

#ifndef PRINT_DEBUG
# define PRINT_DEBUG(x) { DEBUG_MODE && std::cout << x << std::endl; }
#endif 

PmergeMe::PmergeMe(void) { }
PmergeMe::PmergeMe(const PmergeMe& copy): _arr(copy.getVector()) { }
PmergeMe&  PmergeMe::operator=(const PmergeMe& copy) { _arr = copy.getVector(); return (*this); }
PmergeMe::~PmergeMe(void) { }

std::vector<int> PmergeMe::getVector() const {
    return (_arr);
}

std::deque<int> PmergeMe::getDeque() const {
    std::deque<int> deque;

    for (unsigned int i = 0; i < _arr.size(); i++) 
        deque.push_back(_arr[i]);
    return (deque);
}

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s)
{
    return ltrim(rtrim(s, WHITESPACES), WHITESPACES);
}

void    printArr(const std::vector<int>& arr) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i + 1 != arr.size())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

void    printArr(const std::deque<int>& arr) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i + 1 != arr.size())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

std::ostream&   operator<<(std::ostream& output, std::deque<int> arr) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        output << arr[i];
        if (i + 1 != arr.size())
            output << ", ";
    }
    return (output);
}

std::ostream&   operator<<(std::ostream& output, std::vector<int> arr) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        output << arr[i];
        if (i + 1 != arr.size())
            output << ", ";
    }
    return (output);
}

/**
 * @brief Perform basic parsing to check if the value contains:
 *
 * - Non-numeric values other than the symbols
 * 
 * - Integer representation of more than INT_MAX
 * 
 * - Duplicates
 * 
 * @param charToAdd 
 * @return int 0 if successful or -1 otherwise
 */
int    PmergeMe::_parse(const std::string& charToAdd) {
    if (charToAdd.find_first_not_of("1234567890+-*/") != std::string::npos)
        return (-1);
    return (0);
}

/**
 * @brief Add numbers from the provided line to the stack until a handled operator is found.
 * Once found, execute the operation immediately with the previous numbers or return an error if not present.
 * 
 * @param line 
 */
int    PmergeMe::handleAdd(char *line) {
    std::string lineStr = std::string(line);

    while (!lineStr.empty()) {
        int num;
        std::stringstream ss;

        trim(lineStr);
        size_t whitespaceIndex = lineStr.find_first_of(WHITESPACES);
        std::string charToAdd = lineStr.substr(0, whitespaceIndex);
        if (_parse(charToAdd)) {
            return (-1);
        }
        ss << charToAdd;
        ss >> num;
        _arr.push_back(num);
        lineStr.erase(0, whitespaceIndex);
    }
    return (0);
}

/**
 * @brief Get the winners from the pairs in the provided pairs vector
 * 
 * @param pairs The vector containing the pairs to retrieve all the winners from
 * @return `std::vector<int>` - The vector containing all the winners 
 */
std::vector<int>    getWinners(const std::vector<Pair>& pairs) {
    std::vector<int>    winners;

    for (unsigned int i = 0; i < pairs.size(); i++)
        winners.push_back(pairs[i].winner);
    return (winners);
}

std::deque<int>    getWinners(const std::deque<Pair>& pairs) {
    std::deque<int>    winners;

    for (unsigned int i = 0; i < pairs.size(); i++)
        winners.push_back(pairs[i].winner);
    return (winners);
}

/**
 * @brief Get the losers from the pairs in the provided pairs vector
 * 
 * @param pairs The vector containing the pairs to retrieve all the losers from
 * @return `std::vector<int>` - The vector containing all the losers 
 */
std::vector<int>    getLosers(const std::vector<Pair>& pairs) {
    std::vector<int>    losers;

    for (unsigned int i = 0; i < pairs.size(); i++)
        losers.push_back(pairs[i].loser);
    return (losers);
}

std::deque<int>    getLosers(const std::deque<Pair>& pairs) {
    std::deque<int>    losers;

    for (unsigned int i = 0; i < pairs.size(); i++)
        losers.push_back(pairs[i].loser);
    return (losers);
}

/**
 * @brief Use the provided array to generate pairs from the custom Pair struct.
 * 
 * A comparison is made between each number to assign the winners and losers appropriately.
 * 
 * @param arr The integer vector to create pairs from
 * @return `std::vector<Pair>` - The vector of pairs containing winners and losers
 */
std::vector<Pair>   makePairs(const std::vector<int>& arr) {
    std::vector<Pair>   pairs;

    for (unsigned int i = 0; i < arr.size(); i++) {
        Pair    pair;
        if (i + 1 < arr.size()) {
            if (arr[i] < arr[i + 1]) {
                pair.winner = arr[i + 1];
                pair.loser = arr[i];
            } else {
                pair.winner = arr[i];
                pair.loser = arr[i + 1];
            }
            i++;
        } else
            return (pairs);
        pairs.push_back(pair);
    }
    return (pairs);
}

std::deque<Pair>   makePairs(const std::deque<int>& arr) {
    std::deque<Pair>   pairs;

    for (unsigned int i = 0; i < arr.size(); i++) {
        Pair    pair;
        if (i + 1 < arr.size()) {
            if (arr[i] < arr[i + 1]) {
                pair.winner = arr[i + 1];
                pair.loser = arr[i];
            } else {
                pair.winner = arr[i];
                pair.loser = arr[i + 1];
            }
            i++;
        } else
            return (pairs);
        pairs.push_back(pair);
    }
    return (pairs);
}

/**
 * @brief Get the winner paired with the provided loser.
 * 
 * @param pairs The vector array of pairs to look through
 * @param loser The number who's winner is to be found
 * @return `int` - The winner if found, or -1 if not found
 */
int getPairedWinner(const std::vector<Pair>& pairs, unsigned int loser) {
    for (unsigned int i = 0; i < pairs.size(); i++) {
        if (pairs[i].loser == loser)
            return (pairs[i].winner);
    }
    return (-1);
}

int getPairedWinner(const std::deque<Pair>& pairs, unsigned int loser) {
    for (unsigned int i = 0; i < pairs.size(); i++) {
        if (pairs[i].loser == loser)
            return (pairs[i].winner);
    }
    return (-1);
}

/**
 * @brief Generate the Jacobsthal number at the specified index.
 * 
 * @param i index to calculate Jacobsthal number
 * @return `unsigned int` - the calculated Jacobsthal number
 */
unsigned int jacobNum(int i) {
    if (i <= 0)
        return (0);
    if (i == 1)
        return (1);
    return (jacobNum(i - 1) + 2 * jacobNum(i - 2));
}

/*
Jacobsthal Numbers:
    0, 1, 1, 3, 5, 11, 21, ...
Used for insertion of the pend elements into the main chain at every recursion level
    3, 2, 5, 4, 11, 10, 9, 8, 7, 6, ...
Calculated using the length of the pend chain
- Take a number from the jacobsthal series
- Subtract 1 from it and keep going until you hit a number already in the series
- Check if there are these many numbers even present in the pend chain.
- If not, insert the number of elements which is present

If there are 3 elements in the pend:
1, 3, 2

If there are 10 elements in the pend:
1, 3, 2, 5, 4, (11 but doesn't exist), 10, 9, 8, 7, 6

The highest index value you can achieve must be the length of the pend chain
*/
std::vector<int>    generateJacobsthalSequence(unsigned int len) {
    std::vector<int>    seq;

    if (len == 0)
        return (seq);

    for (int i = 2; jacobNum(i) <= len; i++) {
        for (int j = jacobNum(i); j >= 1; j--) {
            if (std::find(seq.begin(), seq.end(), j) != seq.end())
                break ;
            seq.push_back(j);
        }
    }
    if (seq.size() != len) {
        for (int i = len; i >= 1; i--) {
            if (std::find(seq.begin(), seq.end(), i) != seq.end())
                break ;
            seq.push_back(i);
        }
    }
    return (seq);
}

/**
 * @brief Update the order of the losers in the `losers` vector to match the order of the winners of the pairs in the main array
 * 
 * Example: At this iteration
 * Main: 2 (Paired with 0), 5 (Paired with 1)
 * Pend: 1, 0
 * 
 * @param pairs 
 * @param main 
 * @param losers 
 */
void    updatePend(std::vector<Pair>& pairs, std::vector<int>& main, std::vector<int>& losers) {
    int temp;

    for (unsigned int i = 0; i < losers.size(); i++) {
        int pairedWinner = getPairedWinner(pairs, losers[i]);
        if (pairedWinner != -1) {
            unsigned int winnerIndex = std::find(main.begin(), main.end(), pairedWinner) - main.begin();
            if (winnerIndex != i) {
                // Since there is a mismatch of winners and their paired losers in the loser chain, update the order
                temp = losers[winnerIndex];
                losers[winnerIndex] = losers[i];
                losers[i] = temp;
            }
        }
    }
}

void    updatePend(std::deque<Pair>& pairs, std::deque<int>& main, std::deque<int>& losers) {
    int temp;

    for (unsigned int i = 0; i < losers.size(); i++) {
        int pairedWinner = getPairedWinner(pairs, losers[i]);
        if (pairedWinner != -1) {
            unsigned int winnerIndex = std::find(main.begin(), main.end(), pairedWinner) - main.begin();
            if (winnerIndex != i) {
                // Since there is a mismatch of winners and their paired losers in the loser chain, update the order
                temp = losers[winnerIndex];
                losers[winnerIndex] = losers[i];
                losers[i] = temp;
            }
        }
    }
}

/**
 * @brief Search the provided array for the index to insert the given element and return it
 * 
 * Uses the binary search algorithm and compares the element with each mid point and returns the appropriate index at which it can be inserted without unsorting the array.
 * 
 * @param element The element to be inserted 
 * @param arr The array to be searched
 * @return `unsigned int` - The index at which to insert the element 
 */
unsigned int    binarySearch(int element, const std::vector<int>& arr) {
    unsigned int lowerBound = 0;
    unsigned int upperBound = arr.size();
    
    while (lowerBound < upperBound) {
        unsigned int midPoint = lowerBound + (upperBound - lowerBound) / 2;
        
        if (element < arr[midPoint]) {
            upperBound = midPoint;
        } else {
            lowerBound = midPoint + 1;
        }
    }
    return lowerBound;
}

unsigned int    binarySearch(int element, const std::deque<int>& arr) {
    unsigned int lowerBound = 0;
    unsigned int upperBound = arr.size();
    
    while (lowerBound < upperBound) {
        unsigned int midPoint = lowerBound + (upperBound - lowerBound) / 2;
        
        if (element < arr[midPoint]) {
            upperBound = midPoint;
        } else {
            lowerBound = midPoint + 1;
        }
    }
    return lowerBound;
}
/**
 * @brief 
 * # Merge-Insertion Sort
 * 
 * ## (Ford-Johnson Algorithm).
 * 
 * Recursively sorts and returns the provided array of positive integers using the Ford-Johnson algorithm.
 * 
 * Ensures the least comparisons are made to sort the array using:
 * 
 * - Limited range binary searching
 * 
 * - Jacobsthal insertion order
 * 
 * @param initialMain The array of positive integers to be sorted
 * @return `std::vector<int>` - The sorted array
 */
std::vector<int>    PmergeMe::sort(const std::vector<int>& initialMain) {
    // Create a list of losers and winners
    std::vector<int>::iterator insertionIt;
    std::vector<Pair>   pairs;
    std::vector<int>    sortedMain;
    std::vector<int>    pend;

    // Note starting time 
    startTime = clock();

    // Group each number in the provided array into pairs
    pairs = makePairs(initialMain);
    sortedMain = getWinners(pairs);
    pend = getLosers(pairs);

    if (initialMain.size() % 2 != 0)
        pend.push_back(initialMain.back());

    PRINT_DEBUG("Main: " << sortedMain);
    PRINT_DEBUG("Pend: " << pend);
    
    if (sortedMain.size() > 1) {
        sortedMain = sort(sortedMain);
    } else {
        // Final form reached
        // Only one number exists here as the winner therefore simply add it to the main
        PRINT_DEBUG("Base case reached");
        PRINT_DEBUG("Inserting pend elements into main");
        sortedMain.insert(sortedMain.begin(), pend[0]);
        if (pend.size() > 1)
            sortedMain.insert(sortedMain.begin() + binarySearch(pend[1], sortedMain), pend[1]);
        PRINT_DEBUG("Main: " << sortedMain);
        return (sortedMain);
    }

    PRINT_DEBUG("Updating pend to match sortedMain");
    // Reorder the losers array based on the sorted main 
    updatePend(pairs, sortedMain, pend);
    PRINT_DEBUG("Pend: " << pend);
    
    // Generate jacobsthal sequence of indices based on losers length
    std::vector<int> jacobInsertionSeq = generateJacobsthalSequence(pend.size());

    insertionIt = jacobInsertionSeq.begin();

    PRINT_DEBUG("Beginning insertion of pend chain into main chain");
    while (insertionIt != jacobInsertionSeq.end()) {
        int elToInsert = pend[(*insertionIt) - 1];
        if (*insertionIt == 1) {
            PRINT_DEBUG("Inserting " << elToInsert << " immediately since beginning of pend chain");
            sortedMain.insert(sortedMain.begin(), elToInsert);
            insertionIt++;
            continue ;
        }
        // Find the position to insert this loser in based on their paired winner
        int pairedWinner = getPairedWinner(pairs, elToInsert);
        if (pairedWinner != -1) {
            std::vector<int>    subvector;
            for (std::vector<int>::iterator it = sortedMain.begin(); *it < pairedWinner; it++) {
                subvector.push_back(*it);
            }
            PRINT_DEBUG("Inserting " << elToInsert << " using bounded binary search (from " << *sortedMain.begin() << " to " << pairedWinner << ")");
            // Limited range binary search since there is an upperbound
            sortedMain.insert(sortedMain.begin() + binarySearch(elToInsert, subvector), elToInsert);
        } else {
            PRINT_DEBUG("Inserting " << elToInsert << " using unbounded binary search (from " << *sortedMain.begin() << " to " << sortedMain.back() << ")");
            // Full range binary search since no upper bound found
            sortedMain.insert(sortedMain.begin() + binarySearch(elToInsert, sortedMain), elToInsert);
        }
        insertionIt++;
    }

    // Clear all elements of the pend chain
    pend.erase(pend.begin(), pend.end());

    PRINT_DEBUG("Main: " << sortedMain);
    PRINT_DEBUG("Pend: " << pend);

    // Measure end time
    endTime = clock();

    return (sortedMain);
}

std::deque<int>    PmergeMe::sort(const std::deque<int>& initialMain) {
    // Create a list of losers and winners
    std::vector<int>::iterator insertionIt;
    std::deque<Pair>   pairs;
    std::deque<int>    sortedMain;
    std::deque<int>    pend;

    // Note starting time 
    startTime = clock();

    // Group each number in the provided array into pairs
    pairs = makePairs(initialMain);
    sortedMain = getWinners(pairs);
    pend = getLosers(pairs);

    if (initialMain.size() % 2 != 0)
        pend.push_back(initialMain.back());

    PRINT_DEBUG("Main: " << sortedMain);
    PRINT_DEBUG("Pend: " << pend);
    
    if (sortedMain.size() > 1) {
        sortedMain = sort(sortedMain);
    } else {
        // Final form reached
        // Only one number exists here as the winner therefore simply add it to the main
        PRINT_DEBUG("Base case reached");
        PRINT_DEBUG("Inserting pend elements into main");
        sortedMain.insert(sortedMain.begin(), pend[0]);
        if (pend.size() > 1)
            sortedMain.insert(sortedMain.begin() + binarySearch(pend[1], sortedMain), pend[1]);
        PRINT_DEBUG("Main: " << sortedMain);
        return (sortedMain);
    }

    PRINT_DEBUG("Updating pend to match sortedMain");
    // Reorder the losers array based on the sorted main 
    updatePend(pairs, sortedMain, pend);
    PRINT_DEBUG("Pend: " << pend);
    
    // Generate jacobsthal sequence of indices based on losers length
    std::vector<int> jacobInsertionSeq = generateJacobsthalSequence(pend.size());

    insertionIt = jacobInsertionSeq.begin();

    PRINT_DEBUG("Beginning insertion of pend chain into main chain");
    while (insertionIt != jacobInsertionSeq.end()) {
        int elToInsert = pend[(*insertionIt) - 1];
        if (*insertionIt == 1) {
            PRINT_DEBUG("Inserting " << elToInsert << " immediately since beginning of pend chain");
            sortedMain.insert(sortedMain.begin(), elToInsert);
            insertionIt++;
            continue ;
        }
        // Find the position to insert this loser in based on their paired winner
        int pairedWinner = getPairedWinner(pairs, elToInsert);
        if (pairedWinner != -1) {
            std::vector<int>    subvector;
            for (std::deque<int>::iterator it = sortedMain.begin(); *it < pairedWinner; it++) {
                subvector.push_back(*it);
            }
            PRINT_DEBUG("Inserting " << elToInsert << " using bounded binary search (from " << *sortedMain.begin() << " to " << pairedWinner << ")");
            // Limited range binary search since there is an upperbound
            sortedMain.insert(sortedMain.begin() + binarySearch(elToInsert, subvector), elToInsert);
        } else {
            PRINT_DEBUG("Inserting " << elToInsert << " using unbounded binary search (from " << *sortedMain.begin() << " to " << sortedMain.back() << ")");
            // Full range binary search since no upper bound found
            sortedMain.insert(sortedMain.begin() + binarySearch(elToInsert, sortedMain), elToInsert);
        }
        insertionIt++;
    }

    // Clear all elements of the pend chain
    pend.erase(pend.begin(), pend.end());

    PRINT_DEBUG("Main: " << sortedMain);
    PRINT_DEBUG("Pend: " << pend);

    // Measure end time
    endTime = clock();

    return (sortedMain);
}