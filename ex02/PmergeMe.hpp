#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include <limits>
# include <algorithm>
# include <math.h>
# include <sys/time.h>

# ifndef WHITESPACES
#  define WHITESPACES " \n\t\r\v\f"
# endif

# ifndef DEBUG_MODE
#  define DEBUG_MODE false
# endif

struct  Pair {
    unsigned int    winner;
    unsigned int    loser;
};

class   PmergeMe {
    public:
        PmergeMe( void );
        PmergeMe( const PmergeMe& copy );
        PmergeMe&  operator=( const PmergeMe& copy );
        ~PmergeMe( void );

        std::vector<int>    getArr() const;
        int                 handleAdd( char *line );
        std::vector<int>    sort( const std::vector<int>& initialMain );

        clock_t             startTime;
        clock_t             endTime;
        
    private:
        std::vector<int>    _arr; // Only meant for storing the initial set of numbers that are parsed
        int                 _parse( const std::string& charToAdd );
};

void            printArr( const std::vector<int>& arr );
std::ostream&   operator<<( std::ostream& output, std::vector<int> arr );

#endif
