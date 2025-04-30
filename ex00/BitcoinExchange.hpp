#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>

class   BitcoinExchange {
    public:
        BitcoinExchange( void );
        BitcoinExchange( const std::string& databasePath );
        BitcoinExchange( const BitcoinExchange& copy );
        BitcoinExchange&  operator=( const BitcoinExchange& copy );
        ~BitcoinExchange( void );
        void    print( void );
        float   get( const std::string& key ) ;
    
    // Member functions
    private:
        int _populateMap( const std::string& databasePath );

    // Attributes
    private:
        std::map<std::string, float>    _data;

};

#endif
