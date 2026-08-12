#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private :
		std::string target;
	public : 
		PresidentialPardonForm();
		~PresidentialPardonForm();
		PresidentialPardonForm(const std::string &target);
		PresidentialPardonForm(const PresidentialPardonForm &obj);
		PresidentialPardonForm &operator =(const PresidentialPardonForm &obj);

		void execute(Bureaucrat const & executor) const;
};

#endif
