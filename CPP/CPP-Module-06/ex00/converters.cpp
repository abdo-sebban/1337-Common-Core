#include "ScalarConverter.hpp"
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <climits>
#include <limits>

void printSpicial(const std::string &str)
{
	if (str == "nanf")
	{
		float f =  0.0f / 0.0f;
		double d = static_cast<double>(f);

		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << f << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
	}
	else if (str == "+inff")
	{
		float f = 1.0f / 0.0f;
		double d = static_cast<double>(f);

		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << f << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
	}
	else if (str == "-inff")
	{
		float f = -1.0f / 0.0f;
		double d = static_cast<double>(f);

		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << f << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
	}
	else if (str == "nan")
	{
		double d = 0.0 / 0.0;
		float f = static_cast<float>(d);

		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << f << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
	}
	else if (str == "+inf")
	{
		double d = 1.0 / 0.0;
		float f = static_cast<float>(d);

		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << f << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
	}
	else if (str == "-inf")
	{
		double d = -1.0 / 0.0;
		float f = static_cast<float>(d);

		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << f << 'f' << std::endl;
		std::cout << "double: " << d << std::endl;
	}
}

void	convertChar(const std::string& str, size_t& len)
{
	char c;

	if (len == 1)
		c = str[0];
	else
		c = str[1];

	if (std::isprint(c))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}


void convertInt(const std::string& str)
{
	bool negative = (str[0] == '-');
	size_t start = (negative || str[0] == '+') ? 1 : 0;

	std::string num = str.substr(start);

	while (num.length() > 1 && num[0] == '0')
        num.erase(0, 1);
	if ((!negative && (num.length() > 10 ||
		(num.length() == 10 && num > "2147483647"))) ||
		(negative && (num.length() > 10 ||
		(num.length() == 10 && num > "2147483648"))))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	int i = std::atoi(str.c_str());

	char c = static_cast<char>(i);
	float f = static_cast<float>(i);
	double d = static_cast<double>(i);

	std::cout << "char: ";
	if (i < 0 || i > 127)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(c))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;

	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << f << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
}

bool my_isnan(float x)
{
    return (x != x);
}

bool my_isnan(double x)
{
    return (x != x);
}

bool my_isinf(float x)
{
    return (x == 1.0f / 0.0f || x == -1.0f / 0.0f);
}

bool my_isinf(double x)
{
    return (x == 1.0 / 0.0 || x == -1.0 / 0.0);
}

void    convertFloat(const std::string& str)
{
        float f = static_cast<float>(std::atof(str.c_str()));
        bool tolerance = (f == static_cast<int>(f));

        std::cout << "char: ";
        if (my_isnan(f) || my_isinf(f) || f < 0 || f > 127)
                std::cout << "impossible" << std::endl;
        else
        {
                char c = static_cast<char>(f);

                if (std::isprint(c))
                        std::cout << "'" << c << "'" << std::endl;
                else
                        std::cout << "Non displayable" << std::endl;
        }

        std::cout << "int: ";
        if (my_isnan(f) || my_isinf(f) || f < static_cast<float>(MIN_INT) ||f > static_cast<float>(MAX_INT))
                std::cout << "impossible" << std::endl;
        else
        {
                int i = static_cast<int>(f);
                std::cout << i << std::endl;
        }

        std::cout << "float: ";
        if (my_isnan(f))
                std::cout << "nanf" << std::endl;
        else if (my_isinf(f))
                std::cout << (f > 0 ? "+inff" : "-inff") << std::endl;
        else
                std::cout << f << (tolerance ? ".0f" : "f") << std::endl;

        std::cout << "double: ";
        double d = static_cast<double>(f);

        if (my_isnan(d))
                std::cout << "nan" << std::endl;
        else if (my_isinf(d))
                std::cout << (d > 0 ? "+inf" : "-inf") << std::endl;
        else
                std::cout << d << (tolerance ? ".0" : "") << std::endl;
}


void    convertDouble(const std::string& str)
{
        double d = std::atof(str.c_str());
        bool tolerance = (d == static_cast<long long>(d));

        std::cout << "char: ";
        if (my_isnan(d) || my_isinf(d) || d < 0 || d > 127)
                std::cout << "impossible" << std::endl;
        else
        {
                char c = static_cast<char>(d);

                if (std::isprint(c))
                        std::cout << "'" << c << "'" << std::endl;
                else
                        std::cout << "Non displayable" << std::endl;
        }

        std::cout << "int: ";
        if (my_isnan(d) || my_isinf(d) || d < static_cast<double>(MIN_INT) ||d > static_cast<double>(INT_MAX))
                std::cout << "impossible" << std::endl;
        else
        {
                int i = static_cast<int>(d);
                std::cout << i << std::endl;
        }

        std::cout << "float: ";
        if (my_isnan(d))
                std::cout << "nanf" << std::endl;
        else if (my_isinf(d))
                std::cout << (d > 0 ? "+inff" : "-inff") << std::endl;
        else if (d < -MAX_FLOAT || d > MAX_FLOAT)
                std::cout << "impossible" << std::endl;
        else
        {
                float f = static_cast<float>(d);
                std::cout << f
                          << (tolerance ? ".0f" : "f")
                          << std::endl;
        }

        std::cout << "double: ";
        if (my_isnan(d))
                std::cout << "nan" << std::endl;
        else if (my_isinf(d))
                std::cout << (d > 0 ? "+inf" : "-inf") << std::endl;
        else
                std::cout << d
                          << (tolerance ? ".0" : "")
                          << std::endl;
}
