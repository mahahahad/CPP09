#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

#ifndef WHITESPACES
#define WHITESPACES " \n\t\r\v\f"
#endif

class   PmergeMe {
    public:
        PmergeMe( void );
        PmergeMe( const PmergeMe& copy );
        PmergeMe&  operator=( const PmergeMe& copy );
        ~PmergeMe( void );

        std::vector<int> getArr() const;

        int     handleAdd( char *line );
        int     sort( std::vector<int> winners ) ;
        int     printArr( const std::vector<int>& arr ) const;
        
    private:
        std::vector<int>    _arr;
        int                 _parse( const std::string& charToAdd );
};

#endif
