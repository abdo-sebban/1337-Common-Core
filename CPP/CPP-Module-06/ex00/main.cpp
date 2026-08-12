#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./convert [data_type]\n";
		return (0);
	}
	ScalarConverter::convert(argv[1]);
	return (0);
}
