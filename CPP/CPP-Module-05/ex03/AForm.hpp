#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>

class Bureaucrat;
class AForm
{
	private:
		const std::string 	name;
		bool			is_signed;
		const int		grade_sg;
		const int		grade_exec;
	public:
		AForm();
		virtual ~AForm();
		AForm(const AForm &obj);
		AForm(const std::string &name, int grade_sg, int grade_exec);
		AForm& operator=(const AForm &obj);

		class GradeTooHighException : public std::exception
		{
			public :
				const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public : 
				const char* what() const throw();
		};

		class FormNotSignedException : public std::exception
		{
			public :
    				const char *what() const throw();
		};

		const std::string 	getName()	const;
		bool			getIsSigned()	const;
		int 			getGradeSG()	const;
		int			getGradeExec()	const;

		void	beSigned(const Bureaucrat &obj);
		virtual void execute(Bureaucrat const & executor) const = 0;
};

std::ostream &operator<<(std::ostream &os, const AForm &obj);

#endif
