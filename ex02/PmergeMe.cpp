#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) { }
PmergeMe::PmergeMe(const PmergeMe& copy): _arr(copy.getArr()) { }
PmergeMe&  PmergeMe::operator=(const PmergeMe& copy) { _arr = copy.getArr(); return (*this); }
PmergeMe::~PmergeMe(void) { }

std::vector<int> PmergeMe::getArr() const {
    return (_arr);
}

std::vector<int> PmergeMe::getMain() const {
    return (_main);
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

std::vector<int>    getWinners(const std::vector<Pair>& pairs) {
    std::vector<int>    winners;

    for (unsigned int i = 0; i < pairs.size(); i++) {
        winners.push_back(pairs[i].winner);
    }
    return (winners);
}

std::vector<int>    getLosers(const std::vector<Pair>& pairs) {
    std::vector<int>    losers;

    for (unsigned int i = 0; i < pairs.size(); i++) {
        if (pairs[i].loser != -1)
            losers.push_back(pairs[i].loser);
    }
    return (losers);
}

std::vector<Pair>   makePairs(std::vector<int> arr) {
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
        } else {
            pair.winner = arr[i];
            pair.loser = -1;
        }
        pairs.push_back(pair);
    }
    return (pairs);
}

int getPairedWinner(std::vector<Pair> pairs, int loser) {
    for (unsigned int i = 0; i < pairs.size(); i++) {
        if (pairs[i].loser == loser)
            return (pairs[i].winner);
    }
    return (-1);
}

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

int    PmergeMe::sort(std::vector<int> winners) {
    // Create a list of losers and winners
    std::vector<int>::iterator itLoser;
    std::vector<Pair>   pairs;
    std::vector<int>    roundWinners;
    std::vector<int>    roundLosers;

    // Group each number in the provided array into pairs
    pairs = makePairs(winners);
    roundWinners = getWinners(pairs);
    roundLosers = getLosers(pairs);

    if (roundWinners.size() > 1) {
        sort(roundWinners);
    } else {
        // Final form reached
        _main.insert(_main.begin(), roundWinners.begin(), roundWinners.end());
    }

    // Generate jacobsthal sequence of indices based on losers length
    std::vector<int> jacobInsertionSeq = generateJacobsthalSequence(roundLosers.size());

    itLoser = jacobInsertionSeq.begin();
    while (itLoser != jacobInsertionSeq.end()) {
        if (*itLoser == 1) {
            _main.insert(_main.begin(), roundLosers[(*itLoser) - 1]);
            itLoser++;
            continue ;
        }
        // Find the position to insert this loser in based on their paired winner
        int pairedWinner = getPairedWinner(pairs, roundLosers[(*itLoser) - 1]);
        if (pairedWinner != -1) {
            for (std::vector<int>::iterator it = _main.begin(); *it <= pairedWinner; it++) {
                if (roundLosers[(*itLoser) - 1] < *it) {
                    _main.insert(it, roundLosers[(*itLoser) - 1]);
                    break ;
                }
            }
        }
        itLoser++;
    }

    return (0);
}

int    PmergeMe::printArr(const std::vector<int>& arr) const {
    for (unsigned int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i + 1 == arr.size())
            std::cout << std::endl;
        else
            std::cout << ", ";
    }
    return (0);
}
