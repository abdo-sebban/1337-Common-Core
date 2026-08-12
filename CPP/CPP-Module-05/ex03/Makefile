CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = Bureaucrat

SRC = main.cpp \
	Bureaucrat.cpp \
	AForm.cpp \
	ShrubberyCreationForm.cpp \
	RobotomyRequestForm.cpp \
	PresidentialPardonForm.cpp \
	Intern.cpp

OBJ = $(SRC:.cpp=.o)

HEADERS = Bureaucrat.hpp \
	AForm.hpp \
	ShrubberyCreationForm.hpp \
	RobotomyRequestForm.hpp \
	PresidentialPardonForm.hpp \
	Intern.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean 
