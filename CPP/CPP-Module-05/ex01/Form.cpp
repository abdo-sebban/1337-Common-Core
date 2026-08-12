#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("anonymous"), is_signed(false), grade_sg(1), grade_exec(1)
{
}

Form::~Form()
{
}

Form::Form(const Form &obj) : name(obj.name), is_signed(obj.is_signed), grade_sg(obj.grade_sg), grade_exec(obj.grade_exec)
{
}

Form::Form(const std::string &name,int grade_sg,int grade_exec) : name(name),is_signed(false),grade_sg(grade_sg),grade_exec(grade_exec)
{
    if (grade_sg < 1 || grade_exec < 1)
        throw GradeTooHighException();

    if (grade_sg > 150 || grade_exec > 150)
        throw GradeTooLowException();
}


Form& Form::operator=(const Form &obj)
{
	this->is_signed = obj.is_signed;
	return (*this);
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Error: Grade Too High!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Error: Grade Too Low!");
}

const std::string 	&Form::getName() const
{
	return (name);
}

bool		Form::getIsSigned() const
{
	return (is_signed);
}

int 		Form::getGradeSG() const
{
	return (grade_sg);
}

int		Form::getGradeExec() const
{
	return (grade_exec);
}

void Form::beSigned(Bureaucrat &obj)
{
	if (obj.getGrade() <= grade_sg)
		is_signed = true;
	else
		throw Form::GradeTooLowException();
}


std::ostream &operator<<(std::ostream &os, const Form &obj)
{
	os	<< "Name: " << obj.getName()
		<< ", Signed: " << obj.getIsSigned()
       		<< ", Grade Sign: " << obj.getGradeSG()
		<< ", Grade Exec: " << obj.getGradeExec();

    return os;
}

