#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"


PresidentialPardonForm::PresidentialPardonForm() :  AForm("PresidentialPardonForm", 25, 5)
{
	target = "Default";
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) : AForm("PresidentialPardonForm", 25, 5)
{
	this->target = target;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm &obj)
{
	target = obj.target;
	return (*this);
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &obj) : AForm(obj)
{
	target = obj.target;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (!getIsSigned())
    		throw FormNotSignedException();

	if (executor.getGrade() > getGradeExec())
    		throw GradeTooLowException();

	std::cout << target
         	<< " has been pardoned by Zaphod Beeblebrox."
          	<< std::endl;

}


