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

    itLoser = roundLosers.begin();
    while (itLoser != roundLosers.end()) {
        // Find the position to insert this loser in based on their paired winner
        int pairedWinner = getPairedWinner(pairs, *itLoser);
        if (pairedWinner != -1) {
            for (std::vector<int>::iterator it = _main.begin(); *it <= pairedWinner; it++) {
                if (*itLoser < *it) {
                    _main.insert(it, *itLoser);
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
