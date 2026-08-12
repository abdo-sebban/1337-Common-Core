#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "functions.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(time(NULL));

	Base *ptr = generate();

	identify(ptr);
	identify(*ptr);

	delete ptr;
}
