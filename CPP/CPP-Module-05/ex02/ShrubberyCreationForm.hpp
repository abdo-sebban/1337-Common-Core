#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	private:
		std::string target;
	public :
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string &target);
		~ShrubberyCreationForm();
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm &obj);
		ShrubberyCreationForm(const ShrubberyCreationForm &obj);
		void execute(Bureaucrat const & executor) const;
};


#endif
