#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstdlib>
#include <cctype>

class BitcoinExchange
{
    private:
        std::map<std::string, double>   db;
        bool                            isValidDate(const std::string &date)        const;
        double                          parseValue(const std::string &valueStr)     const;
        double                          getRate(const std::string &date)            const;
        void                            processLine(const std::string &line)        const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void    loadDatabase(const std::string &filename);
        void    processInput(const std::string &filename) const;

        class FileException : public std::exception
        {
            public:
                const char *what() const throw();
        };
    
        class DatabaseException : public std::exception
        {
            public:
                const char *what() const throw();
        };
    
        class BadInputException : public std::exception
        {
            public:
                const char *what() const throw();
        };
    
        class NegativeValueException : public std::exception
        {
            public:
                const char *what() const throw();
        };
    
        class TooLargeValueException : public std::exception
        {
            public:
                const char *what() const throw();
        };
    
        class NoRateException : public std::exception
        {
            public:
                const char *what() const throw();
        };
};

#endif