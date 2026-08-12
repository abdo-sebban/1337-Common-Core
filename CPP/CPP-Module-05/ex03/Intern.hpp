#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern &obj);
		Intern &operator=(const Intern &obj);
		~Intern();

		AForm *makeForm(const std::string &name, const std::string &target);
};

#endif
