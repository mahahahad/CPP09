#include "RPN.hpp"

RPN::RPN(void) { }
RPN::RPN(const RPN& copy) { (void) copy; }
RPN&  RPN::operator=(const RPN& copy) { (void) copy; return (*this); }
RPN::~RPN(void) { }

//TODO: Improve this and handle multiple numbers in single line
void    RPN::parseAndAdd(char *line) {
    _queue.push(line);
    // std::cout << line << std::endl;
}

int     RPN::evaluate(void) {
    int result = 0;
    int i = 0;
    while (!_queue.empty()) {
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
