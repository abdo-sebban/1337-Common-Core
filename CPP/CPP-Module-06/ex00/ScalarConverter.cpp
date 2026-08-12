#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &obj)
{
	(void)obj;
	return (*this);
}

ScalarConverter::ScalarConverter(const ScalarConverter &obj)
{
	(void)obj;
}

void    ScalarConverter::convert(const std::string& str)
{
	size_t len = str.length();
	Type type = detectType(str, len);

	switch(type)
	{
		case INVALID:
			std::cout << "Invalid input" << std::endl;
			break;
		case SPECIAL:
			printSpicial(str);
			break;
		case CHAR:
			convertChar(str, len);
			break;
		case INT:
			convertInt(str);
			break;
		case FLOAT:
			convertFloat(str);
			break;
		case DOUBLE:
			convertDouble(str);
			break;
	}
}
