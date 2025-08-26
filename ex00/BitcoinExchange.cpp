#include "BitcoinExchange.hpp"

bool    isValidDate(const std::string& date) {
    std::size_t dashIndex[2] = { date.find('-'), date.find('-', dashIndex[0] + 1) };
    std::string year;
    std::string month;
    std::string day;

    // No dashes found, return false immediately
    if (dashIndex[0] == std::string::npos || dashIndex[1] == std::string::npos)
        return (false);
    
    year = date.substr(0, dashIndex[0]);
    month = date.substr(dashIndex[0] + 1, dashIndex[1] - dashIndex[0] - 1);
    day = date.substr(dashIndex[1] + 1);

    // Enforce YYYY-MM-DD
    if (year.length() != 4 || month.length() != 2 || day.length() != 2)
        return (false);
    
    // Check valid dates
    if (month > "12" || day > "31")
        return (false);
    return (true);
}

/**
 * @brief Create a Date object from the provided date string
 * 
 * @param date The string to create the date object from
 * @return Date The created date object
 */
Date    createDate(const std::string& date) {
    Date    createdDate;
    std::stringstream   year;
    std::stringstream   month;
    std::stringstream   day;

    year << date.substr(0, 4);
    year >> createdDate.year;
    month << date.substr(5, 2);
    month >> createdDate.month;
    day << date.substr(8, 2);
    day >> createdDate.day;
    return (createdDate);
}

bool    Date::operator<(const Date& date) const {
    if (this->year != date.year)
        return (this->year < date.year);
    if (this->month != date.month)
        return (this->month < date.month);
    return (this->day < date.day);
}

bool    Date::operator>(const Date& date) const {
    if (this->year != date.year)
        return (this->year > date.year);
    if (this->month != date.month)
        return (this->month > date.month);
    return (this->day > date.day);
}

bool    Date::operator!=(const Date& date) const {
    return (this->year != date.year || this->month != date.month || this->day != date.day);
}

bool    Date::operator==(const Date& date) const {
    return (this->year == date.year && this->month == date.month && this->day == date.day);
}

std::ostream&   operator<<(std::ostream& output, const Date& date) {
    output << date.year << "-" << date.month << "-" << date.day;
    return (output);
}

const char* BitcoinExchange::InvalidDatabaseException::what() const throw() {
    return ("invalid database.");
}

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

    if (!db.good()) {
        return (1);
    }
    while (getline(db, line).good()) {
        std::stringstream   valueStr;
        std::size_t         commaIndex = line.find(',');
        
        if (commaIndex == std::string::npos)
            continue ;
        if (isValidDate(line.substr(0, commaIndex)) == false)
            continue ;
        valueStr << line.substr(commaIndex + 1);
        if (valueStr.str().empty())
            continue ;
        valueStr >> value;
        _data[createDate(line.substr(0, commaIndex))] = value;
    }
    return (0);
}

BitcoinExchange::BitcoinExchange() {
    if (_populateMap())
        throw(InvalidDatabaseException());
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

void    BitcoinExchange::print() {
    for (
        std::map<Date, float>::const_iterator it = _data.begin();
        it != _data.end();
        ++it
    ) {
        std::cout.setf(std::ios::fixed);
        std::cout << it->first << " = " << std::setprecision(2) << it->second << ";\n";
    }
}

float   BitcoinExchange::get(const std::string& key) {
    Date    date = createDate(key);
    std::map<Date, float>::iterator it = _data.lower_bound(date);

    if (it->first != date && it != _data.begin()) {
        --it;
        // std::cout << date << " matched with " << it->first << std::endl;
        return (it->second);
    }
    // std::cout << date << " matched with " << it->first << std::endl;
    return (it->second);
}
