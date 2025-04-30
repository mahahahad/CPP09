#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <queue>
#include <sstream>

class   RPN {
    public:
        RPN( void );
        RPN( const RPN& copy );
        RPN&  operator=( const RPN& copy );
        ~RPN( void );
        void    parseAndAdd( char *line );
        int     evaluate( void ) ;

    private:
        std::queue<std::string> _queue;
};

#endif
