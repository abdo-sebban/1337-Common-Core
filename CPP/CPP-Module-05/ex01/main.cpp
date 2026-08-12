#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	Bureaucrat 	obj_br("bureacrat_1");
	Form 		obj_fr("form_1", 110, 11);
	obj_br.signForm(obj_fr);
}

