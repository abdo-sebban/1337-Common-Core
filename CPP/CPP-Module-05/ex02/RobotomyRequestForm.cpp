#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45)
{
	target = "Default";
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) :  AForm("RobotomyRequestForm", 72, 45)
{
	this->target = target;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &obj)
{
	target = obj.target;
	return (*this);
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &obj) : AForm(obj)
{
	target = obj.target;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (!getIsSigned())
        	throw FormNotSignedException();

    	if (executor.getGrade() > getGradeExec())
        	throw GradeTooLowException();

    	std::cout << "* DRRRRRRRR DRILLING NOISES *" << std::endl;

    	if (rand() % 2)
    	{
        	std::cout << target << " has been robotomized successfully" << std::endl;
    	}
    	else
    	{
        	std::cout << "Robotomy failed on " << target << std::endl;
	}
}


