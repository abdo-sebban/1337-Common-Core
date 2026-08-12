#include "ScalarConverter.hpp"
#include <string>
#include <cctype>

static int	isSpecial(const std::string &str)
{
	if (str == "nan" || str == "nanf" || str == "+inf" || str == "+inff" || str == "-inf" || str == "-inff")
		return 1;
	return (0);
}

static int	isChar(const std::string& str , size_t&len)
{
	if (len == 1 && !isdigit(str[0]))
		return (1);
	if (len == 3 && str[0] == '\'' && str[2] == '\'')
		return (1);
	return (0);
}

static bool isInt(const std::string& str)
{
	size_t i = 0;

	if (str.empty())
		return false;

	if (str[0] == '+' || str[0] == '-')
		i++;

	if (i == str.length())
		return false;

	while (i < str.length())
	{
		if (!std::isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

static bool isDouble(const std::string& str)
{
	size_t dot = str.find('.');

	if (dot == std::string::npos) 
		return false;

	if (dot == 0 || dot == str.length() - 1)
		return false;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (i == dot)
			continue;

		if ((i == 0) && (str[i] == '+' || str[i] == '-'))
			continue;

		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

static bool isFloat(const std::string& str)
{
	if (str.length() < 2)
		return false;

	if (str[str.length() - 1] != 'f')
		return false;

	std::string tmp = str.substr(0, str.length() - 1);

	return isDouble(tmp);
}



Type detectType(const std::string& str, size_t &len)
{
	if (isSpecial(str))
		return SPECIAL;

	if (isChar(str, len))
		return CHAR;

	if (isInt(str))
		return INT;

	if (isFloat(str))
		return FLOAT;

	if (isDouble(str))
		return DOUBLE;

	return INVALID;
}
