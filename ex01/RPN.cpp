#include "RPN.hpp"

RPN::RPN(void) { }
RPN::RPN(const RPN& copy) { (void) copy; }
RPN&  RPN::operator=(const RPN& copy) { (void) copy; return (*this); }
RPN::~RPN(void) { }


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

//TODO: Improve this EVEN FURTHER
void    RPN::parseAndAdd(char *line) {
    std::string lineStr = std::string(line);
    while (!lineStr.empty()) {
        trim(lineStr);
        size_t whitespaceIndex = lineStr.find_first_of(WHITESPACES);
        if (whitespaceIndex == lineStr.npos) {
            _queue.push(lineStr);
            break ;
        }
        else {
            _queue.push(lineStr.substr(0, whitespaceIndex));
            lineStr.erase(0, whitespaceIndex);
        }
    }
}

int     RPN::evaluate(void) {
    int result = 0;
    int i = 0;

    if (_queue.size() < 3) {
        std::cerr << "Error: insufficient numbers provided." << std::endl;
        return (0);
    }
    while (!_queue.empty() && _queue.size() >= 2) {
        std::stringstream num1Str;
        std::stringstream num2Str;
        int num2Int;
        std::string operation;
        if (i == 0) {
            num1Str << _queue.front();
            num1Str >> result;
            _queue.pop();
            // std::cout << num1Str.str() << std::endl;
        }
        num2Str << _queue.front();
        num2Str >> num2Int;
        _queue.pop();
        // std::cout << num2Str.str() << std::endl;

        operation = _queue.front();
        _queue.pop();
        // std::cout << operation << std::endl;
        
        if (operation == "+")
            result += num2Int;
        else if (operation == "-")
            result -= num2Int;
        else if (operation == "*")
            result *= num2Int;
        else if (operation == "/")
            result /= num2Int;
        i++;
    }
    return (result);
}
