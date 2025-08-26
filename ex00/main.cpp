#include "BitcoinExchange.hpp"

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s)
{
    const char* ws = " \t\n\r\f\v";
    return ltrim(rtrim(s, ws), ws);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }
    try {
        BitcoinExchange btcExchange;
        std::ifstream   inputFile(argv[1]);

        if (!inputFile.good()) {
            std::cerr << "Error: could not open file." << std::endl;
            return (1);
        }

        std::string line;
        while (inputFile.good()) {
            getline(inputFile, line);
            if (line == "")
                continue ;
            size_t  pipePos = line.find("|");
            if (pipePos == line.npos) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue ;
            }
            std::string date = line.substr(0, pipePos);
            std::string valueString = line.substr(pipePos + 1);
            trim(date);
            trim(valueString);

            // Ignore the header
            if (date == "date")
                continue ;
            
            if (isValidDate(date) == false) {
                std::cerr << "Error: invalid date (must be YYYY-MM-DD) => " << line << std::endl;
                continue ;
            }
            
            if (valueString.empty()) {
                std::cerr << "Error: bad input (value not provided) => " << line << std::endl;
                continue ;
            }

            std::stringstream valueStream;
            float   valueFloat;
            char    c;
            valueStream << valueString;
            valueStream >> valueFloat;

            if (valueStream.get(c) || valueStream.bad()) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue ;
            }
            
            if (valueFloat <= 0) {
                std::cerr << "Error: not a positive number." << std::endl;
                continue ;
            }
            if (valueFloat > 1000) {
                std::cerr << "Error: too large a number." << std::endl;
                continue ;
            }

            std::cout
                << date << " => " << valueString << " = "
                << valueFloat * btcExchange.get(date)
                << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }
    return (0);
}
