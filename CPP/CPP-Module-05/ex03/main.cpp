#include "Intern.hpp"

int main()
{
	Intern intern;

	AForm *f1 = intern.makeForm("robotomy request", "Bender");
	AForm *f2 = intern.makeForm("presidential pardon", "Arthur");
	AForm *f3 = intern.makeForm("shrubbery creation", "home");
	AForm *f4 = intern.makeForm("bad form", "test");

	delete f1;
	delete f2;
	delete f3;
	delete f4;

	return (0);
}
