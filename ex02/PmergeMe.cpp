#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) { }
PmergeMe::PmergeMe(const PmergeMe& copy): _arr(copy.getArr()) { }
PmergeMe&  PmergeMe::operator=(const PmergeMe& copy) { _arr = copy.getArr(); return (*this); }
PmergeMe::~PmergeMe(void) { }

std::vector<int> PmergeMe::getArr() const {
    return (_arr);
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

int    PmergeMe::sort(std::vector<int> winners) {
    // Create a list of losers and winners
    std::vector<int> losers;
    std::vector<int>::iterator it = winners.begin();

    // Make pairs and compare between each
    while (it != winners.end()) {
        // Check if next is present
        if (it + 1 != winners.end()) {
            // std::cout << "Current: " << *it << std::endl;
            // std::cout << "Next: " << *(it + 1) << std::endl;
            if (*it < *(it + 1)) {
                // std::cout << *(it + 1) << " is greater than " << *it << std::endl;
                losers.push_back(*it);
                winners.erase(it);
            } else {
                // std::cout << *(it + 1) << " is lesser than " << *it << std::endl;
                losers.push_back(*(it + 1));
                winners.erase(it + 1);
            }
            it++;
        } else
            break ;
    }

    // printArr(winners);

    // Check if the list of winners contains more than 1 element
    // Call itself if it does until it doesn't
    if (winners.size() != 1)
        sort(winners);
    else {
        _arr.clear();
        _arr.insert(_arr.begin(), winners.begin(), winners.end());
    }
    
    // Insert losers into the main _arr vector
    _arr.insert(_arr.begin(), losers.begin(), losers.end());
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
