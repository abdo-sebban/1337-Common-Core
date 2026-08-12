#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137)
{
	target = "Default";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm", 145, 137)
{
	this->target = target;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &obj)
{
	target = obj.target;
	return(*this);
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &obj) : AForm(obj)
{
	target = obj.target;
}


void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (!getIsSigned())
		throw FormNotSignedException();

	if (executor.getGrade() > getGradeExec())
        	throw GradeTooLowException();

	std::ofstream file((target + "_shrubbery").c_str());
	if (!file.is_open())
    		return;

	file << "   /\\\n";
	file << "  /**\\\n";
	file << " /****\\\n";
	file << "/******\\\n";
	file << "   ||\n";
}
