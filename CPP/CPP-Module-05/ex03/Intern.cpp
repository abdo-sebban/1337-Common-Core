#include "Intern.hpp"

Intern::Intern()
{
}

Intern::~Intern()
{
}

Intern::Intern(const Intern &obj)
{
	(void)obj;
}

Intern &Intern::operator=(const Intern &obj)
{
	(void)obj;
	return (*this);
}

AForm *Intern::makeForm(const std::string &name,
			const std::string &target)
{
	std::string forms[3];

	forms[0] = "shrubbery creation";
	forms[1] = "robotomy request";
	forms[2] = "presidential pardon";

	for (int i = 0; i < 3; i++)
	{
		if (name == forms[i])
		{
			std::cout << "Intern creates " << name << std::endl;

			if (i == 0)
				return (new ShrubberyCreationForm(target));
			if (i == 1)
				return (new RobotomyRequestForm(target));
			if (i == 2)
				return (new PresidentialPardonForm(target));
		}
	}

	std::cout << "Error: unknown form \"" << name << "\"" << std::endl;
	return (NULL);
}
