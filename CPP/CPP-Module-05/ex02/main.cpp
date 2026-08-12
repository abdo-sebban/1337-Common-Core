#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
	srand(std::time(NULL));
	try
	{
		Bureaucrat boss("Boss", 1);

		ShrubberyCreationForm shrub("home");
		RobotomyRequestForm robot("Bender");
		PresidentialPardonForm pardon("Arthur Dent");

		boss.signForm(shrub);
		boss.executeForm(shrub);

		boss.signForm(robot);
		boss.executeForm(robot);

		boss.signForm(pardon);
		boss.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return (0);
}
