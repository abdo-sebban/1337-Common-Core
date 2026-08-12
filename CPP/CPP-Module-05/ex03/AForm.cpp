#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : name("anonymous"), is_signed(false), grade_sg(1), grade_exec(1)
{
}

AForm::~AForm()
{
}

AForm::AForm(const AForm &obj) : name(obj.name), is_signed(obj.is_signed), grade_sg(obj.grade_sg), grade_exec(obj.grade_exec)
{
}

AForm::AForm(const std::string &name,int grade_sg,int grade_exec) : name(name),is_signed(false),grade_sg(grade_sg),grade_exec(grade_exec)
{
    if (grade_sg < 1 || grade_exec < 1)
        throw GradeTooHighException();

    if (grade_sg > 150 || grade_exec > 150)
        throw GradeTooLowException();
}

AForm& AForm::operator=(const AForm &obj)
{
	this->is_signed = obj.is_signed;
	return (*this);
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Error: Grade Too High!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Error: Grade Too Low!");
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return "Form not signed";
}

const std::string 	AForm::getName() const
{
	return (name);
}

bool		AForm::getIsSigned() const
{
	return (is_signed);
}

int 		AForm::getGradeSG() const
{
	return (grade_sg);
}

int		AForm::getGradeExec() const
{
	return (grade_exec);
}


void AForm::beSigned(const Bureaucrat &obj)
{
	if (obj.getGrade() <= grade_sg)
        	is_signed = true;
	else
        	throw GradeTooLowException();
}


std::ostream &operator<<(std::ostream &os, const AForm &obj)
{
	os	<< "Name: " << obj.getName()
		<< ", Signed: " << obj.getIsSigned()
       		<< ", Grade Sign: " << obj.getGradeSG()
		<< ", Grade Exec: " << obj.getGradeExec();

    return os;
}
