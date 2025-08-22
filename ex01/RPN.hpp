#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <limits>

#ifndef WHITESPACES
#define WHITESPACES " \n\t\r\v\f"
#endif

class   RPN {
    public:
        RPN( void );
        RPN( const RPN& copy );
        RPN&  operator=( const RPN& copy );
        ~RPN( void );

        std::stack<long> getStack() const;
        bool    getHasError() const;

        int     handleAdd( char *line );
        int     evaluate( const std::string& op ) ;
        int     printResult() const;
        
    private:
        std::stack<long>    _stack;
        bool                _hasError;
        int                 _parse( const std::string& charToAdd );
};

#endif
