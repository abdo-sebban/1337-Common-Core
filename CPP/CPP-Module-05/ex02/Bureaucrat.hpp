#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

class AForm;
class Bureaucrat
{
	private:
		const std::string	name;
		int			grade;
	public:
		Bureaucrat();
		~Bureaucrat();
		Bureaucrat(const std::string &name);
		Bureaucrat(const std::string &name, int grade);
		Bureaucrat& operator=(const Bureaucrat &obj);
		Bureaucrat(const Bureaucrat &obj);

		class GradeTooHighException : public std::exception
		{
			public :
				const char *what() const throw();
		};
		
		class GradeTooLowException  : public std::exception
		{
			public :
				const char *what() const throw();
		};

		const std::string	&getName() const;
		int			getGrade() const;
		void			increment();
		void			decrement();

		void			signForm(AForm &obj);
		void			executeForm(AForm const &form) const;
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj);

#endif
