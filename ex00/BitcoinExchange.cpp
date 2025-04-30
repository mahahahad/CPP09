#include "BitcoinExchange.hpp"

/**
 * @brief Read everything from the database and update the map container
 * using these key-value pairs.
 * 
 * @return int The status of the operation
 */
int BitcoinExchange::_populateMap(
    const std::string& databasePath = "data.csv"
) {
    std::ifstream       db(databasePath.c_str());
    std::string         line;
    float               value;

    while (getline(db, line).good()) {
        std::stringstream   valueStr;
        valueStr << line.substr(
            line.find(',') + 1, line.size() - line.find(',') + 1
        );
        valueStr >> value;
        _data[line.substr(0, line.find(','))] = value;
    }
    return (0);
}

BitcoinExchange::BitcoinExchange(void) {
    _populateMap();
}

BitcoinExchange::BitcoinExchange(const std::string& databasePath) {
    _populateMap(databasePath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy):
    _data(copy._data) { }

BitcoinExchange&  BitcoinExchange::operator=(const BitcoinExchange& copy) {
    _data = copy._data;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() { }

void    BitcoinExchange::print(void) {
    for (
        std::map<std::string, float>::const_iterator it = _data.begin();
        it != _data.end();
        ++it
    ) {
        std::cout.setf(std::ios::fixed);
        std::cout << it->first << " = " << std::setprecision(2) << it->second << ";\n";
    }
}

float   BitcoinExchange::get(const std::string& key) {
    std::map<std::string, float>::iterator it = _data.lower_bound(key);

    if (it->first != key) {
        --it;
        // std::cout << key << " matched with " << it->first << std::endl;
        return (it->second);
    }
    // std::cout << key << " matched with " << it->first << std::endl;
    return (it->second);
}
