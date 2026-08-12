#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat obj("asebban");
		obj.decrement();
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "continue the execution steps ..." << std::endl;

	try
	{
		Bureaucrat obj("asebban", 1);
		std::cout << obj << std::endl;
		obj.increment();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

}

