#include "RPN.hpp"

RPN::RPN(void): _hasError(false) { }
RPN::RPN(const RPN& copy): _stack(copy.getStack()), _hasError(copy.getHasError()) { }
RPN&  RPN::operator=(const RPN& copy) { _stack = copy.getStack(); _hasError = copy.getHasError(); return (*this); }
RPN::~RPN(void) { }

std::stack<long> RPN::getStack() const {
    return (_stack);
}

bool    RPN::getHasError() const {
    return (_hasError);
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
 * - Integer representation of more than 10
 * 
 * - A decimal or brackets
 * 
 * - Non-numeric values other than the symbols
 * 
 * @param charToAdd 
 * @return int 0 if successful or -1 otherwise
 */
int    RPN::_parse(const std::string& charToAdd) {
    if (charToAdd.length() > 1 && (charToAdd.length() == 2 && (charToAdd[0] != '+' && charToAdd[0] != '-')))
        return (-1);
    if (charToAdd.find_first_of(".()") != std::string::npos)
        return (-1);
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
int    RPN::handleAdd(char *line) {
    std::string lineStr = std::string(line);

    while (!lineStr.empty()) {
        trim(lineStr);
        size_t whitespaceIndex = lineStr.find_first_of(WHITESPACES);
        std::string charToAdd = lineStr.substr(0, whitespaceIndex);
        if (_parse(charToAdd)) {
            _hasError = true;
            return (-1);
        }
        if (charToAdd.length() == 1 && charToAdd.find_first_of("+-*/") != std::string::npos) {
            if (evaluate(charToAdd)) {
                _hasError = true;
                return (-1);
            }
        } else {
            long num;
            std::stringstream ss;
            ss << charToAdd;
            ss >> num;
            _stack.push(num);
        }
        lineStr.erase(0, whitespaceIndex);
    }
    return (0);
}

int    RPN::evaluate(const std::string& op) {
    long num2;
    long num1;
    
    if (_stack.size() < 2)
        return (-1);
    num2 = _stack.top();
    _stack.pop();
    num1 = _stack.top();
    _stack.pop();
    if (op == "+")
        _stack.push(num1 + num2);
    if (op == "-")
        _stack.push(num1 - num2);
    if (op == "*")
        _stack.push(num1 * num2);
    if (op == "/") {
        if (num1 == 0 || num2 == 0)
            return (-1);
        _stack.push(num1 / num2);
    }
    return (0);
}

int    RPN::printResult() const {
    // Only print the result if there is no error
    if (_hasError || _stack.size() != 1 || std::numeric_limits<int>::max() < _stack.top() || std::numeric_limits<int>::min() > _stack.top()) {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    std::cout << _stack.top() << std::endl;
    return (0);
}
