#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default")
{
	grade = 150;
}

Bureaucrat::~Bureaucrat()
{

}

Bureaucrat::Bureaucrat(const std::string &name) : name(name)
{
	grade = 150;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name)
{
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else
		this->grade = grade;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &obj)
{
	grade = obj.grade;
	return (*this);
}

Bureaucrat::Bureaucrat(const Bureaucrat &obj) : name(obj.name)
{
	grade = obj.grade;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("ERROR : Grade Too High!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("ERROR : Grade Too Low!");
}

const std::string& Bureaucrat::getName() const
{
	return (name);
}

int Bureaucrat::getGrade() const
{
	return (grade);
}

void Bureaucrat::increment()
{
	if (grade == 1)
		throw Bureaucrat::GradeTooHighException();
	grade--;
}

void Bureaucrat::decrement()
{
	if (grade == 150)
		throw Bureaucrat::GradeTooLowException();
	grade++;
}


std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj)
{
	os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".";
	return (os);
}

