#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>

# define MIN_INT	-2147483648
# define MAX_INT	2147483647
# define MIN_FLOAT 	-3.40282e+38
# define MAX_FLOAT	3.40282e+38
# define MIN_DOUBLE	-1.79769e+308
# define MAX_DOUBLE	1.79769e+308


enum Type
{
	SPECIAL = 0,
	CHAR = 1,
	INT = 2,
	FLOAT = 3,
	DOUBLE = 4,
	INVALID = -1
};

class ScalarConverter
{		
	private:
		ScalarConverter(void);
		~ScalarConverter(void);
		ScalarConverter& operator=(const ScalarConverter &obj);
		ScalarConverter(const ScalarConverter &obj);
	
	public:	
		static void convert(const std::string &str);
};


Type	detectType(const std::string &str, size_t &len);
void	printSpicial(const std::string& str);
void	convertChar(const std::string& str, size_t &len);
void	convertInt(const std::string& str);
void	convertFloat(const std::string &str);
void	convertDouble(const std::string &str);

#endif
