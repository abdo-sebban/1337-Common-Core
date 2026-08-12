#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string target;
	public:
		RobotomyRequestForm();
		~RobotomyRequestForm();
		RobotomyRequestForm(const std::string &target);
		RobotomyRequestForm& operator=(const RobotomyRequestForm &obj);
		RobotomyRequestForm(const RobotomyRequestForm &obj);

		void execute(Bureaucrat const &executor) const;
};

#endif
