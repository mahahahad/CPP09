#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>

struct  Date {
    short int   year;
    short int   month;
    short int   day;

    bool        operator==( const Date& date ) const;
    bool        operator!=( const Date& date ) const;
    bool        operator>( const Date& date ) const;
    bool        operator<( const Date& date ) const;
};

class   BitcoinExchange {
    public:
        BitcoinExchange();
        BitcoinExchange( const std::string& databasePath );
        BitcoinExchange( const BitcoinExchange& copy );
        BitcoinExchange&  operator=( const BitcoinExchange& copy );
        ~BitcoinExchange();
        void    print();
        float   get( const std::string& key ) ;
    
    public:
        class   InvalidDatabaseException: public std::exception {
            public:
                virtual const char*   what() const throw();
        };
    
    // Member functions
    private:
        int _populateMap( const std::string& databasePath );

    // Attributes
    private:
        std::map<Date, float>    _data;
};

bool    isValidDate( const std::string& date );
std::ostream&   operator<<( std::ostream& output, const Date& date);

#endif
