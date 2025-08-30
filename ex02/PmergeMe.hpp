#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

#ifndef WHITESPACES
#define WHITESPACES " \n\t\r\v\f"
#endif

struct  Pair {
    unsigned int    winner;
    int             loser;
};

std::vector<int>    getWinners( const std::vector<Pair>& pairs );

class   PmergeMe {
    public:
        PmergeMe( void );
        PmergeMe( const PmergeMe& copy );
        PmergeMe&  operator=( const PmergeMe& copy );
        ~PmergeMe( void );

        std::vector<int> getArr() const;
        std::vector<int> getMain() const;

        int     handleAdd( char *line );
        int     sort( std::vector<int> winners ) ;
        int     printArr( const std::vector<int>& arr ) const;
        
    private:
        std::vector<int>    _arr;
        std::vector<int>    _main;
        int                 _parse( const std::string& charToAdd );
};

#endif
