#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>


class Bureaucrat;
class Form
{
	private:
		const std::string 	name;
		bool			is_signed;
		const int		grade_sg;
		const int		grade_exec;
	public:
		Form();
		~Form();
		Form(const Form &obj);
		Form(const std::string &name, int grade_sg, int grade_exec);
		Form& operator=(const Form &obj);

		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw();
		};

		const std::string 	&getName()	const;
		bool			getIsSigned()	const;
		int 			getGradeSG()	const;
		int			getGradeExec()	const;

		void beSigned(Bureaucrat &obj);
};

std::ostream &operator<<(std::ostream &os, const Form &obj);

#endif
