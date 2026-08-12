#include "BitcoinExchange.hpp"

static bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static std::string trim(const std::string &s)
{
    size_t start = 0;
    size_t end = s.size();

    while (start < end && std::isspace(static_cast<unsigned char>(s[start])))
        ++start;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;
    return s.substr(start, end - start);
}

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : db(other.db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        db = other.db;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

const char *BitcoinExchange::FileException::what() const throw()
{
    return "Error: could not open file.";
}

const char *BitcoinExchange::DatabaseException::what() const throw()
{
    return "Error: invalid database file.";
}

const char *BitcoinExchange::BadInputException::what() const throw()
{
    return "Error: bad input";
}

const char *BitcoinExchange::NegativeValueException::what() const throw()
{
    return "Error: not a positive number.";
}

const char *BitcoinExchange::TooLargeValueException::what() const throw()
{
    return "Error: too large a number.";
}

const char *BitcoinExchange::NoRateException::what() const throw()
{
    return "Error: no exchange rate available for this date.";
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.size() != 10)
        return (false);
    if (date[4] != '-' || date[7] != '-')
        return (false);
    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return (false);
    if (day < 1)
        return (false);

    static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysPerMonth[month - 1];
    if (month == 2 && isLeapYear(year))
        maxDay = 29;
    if (day > maxDay)
        return (false);
    return (true);
}

double BitcoinExchange::parseValue(const std::string &valueStr) const
{
    if (valueStr.empty())
        throw BadInputException();

    const char *cstr = valueStr.c_str();
    char       *endptr = NULL;

    errno = 0;
    double value = std::strtod(cstr, &endptr);

    if (endptr == cstr)
        throw BadInputException();
    while (*endptr != '\0')
    {
        if (!std::isspace(static_cast<unsigned char>(*endptr)))
            throw BadInputException();
        ++endptr;
    }
    if (errno == ERANGE)
        throw TooLargeValueException();
    if (value < 0)
        throw NegativeValueException();
    if (value > 1000)
        throw TooLargeValueException();
    return value;
}

double BitcoinExchange::getRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = db.lower_bound(date);

    if (it != db.end() && it->first == date)
        return it->second;
    if (it == db.begin())
        throw NoRateException();
    --it;
    return it->second;
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream   file(filename.c_str());
    if (!file.is_open())
        throw FileException();

    std::string line;
    bool        firstLine = true;

    while (std::getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty())
            continue;
        if (firstLine)
        {
            firstLine = false;
            if (trimmed.find("date") != std::string::npos)
                continue;
        }

        size_t pos = trimmed.find(',');
        if (pos == std::string::npos)
            throw DatabaseException();

        std::string date    = trim(trimmed.substr(0, pos));
        std::string rateStr = trim(trimmed.substr(pos + 1));

        if (!isValidDate(date))
            throw DatabaseException();

        char *endptr = NULL;
        errno = 0;
        double rate = std::strtod(rateStr.c_str(), &endptr);
        if (endptr == rateStr.c_str() || *endptr != '\0' || errno == ERANGE || rate < 0)
            throw DatabaseException();

        db[date] = rate;
    }
    file.close();

    if (db.empty())
        throw DatabaseException();
}

void BitcoinExchange::processLine(const std::string &line) const
{
    std::string trimmed = trim(line);

    size_t pos = trimmed.find('|');
    if (pos == std::string::npos)
        throw BadInputException();

    std::string datePart  = trim(trimmed.substr(0, pos));
    std::string valuePart = trim(trimmed.substr(pos + 1));

    if (!isValidDate(datePart))
        throw BadInputException();

    double value  = parseValue(valuePart);
    double rate   = getRate(datePart);
    double result = value * rate;

    std::cout << datePart << " => " << valuePart << " = " << result << std::endl;
}


void BitcoinExchange::processInput(const std::string &filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw FileException();

    std::string line;
    bool        firstLine = true;

    while (std::getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty())
            continue;
        if (firstLine)
        {
            firstLine = false;
            if (trimmed == "date | value")
                continue;
        }
        try
        {
            processLine(line);
        }
        catch (const BadInputException &e)
        {
            (void)e;
            std::cerr << "Error: bad input => " << trimmed << std::endl;
        }
        catch (const NegativeValueException &e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (const TooLargeValueException &e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (const NoRateException &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    file.close();
}