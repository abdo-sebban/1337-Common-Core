CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = Materia

SRCS = main.cpp \
       AMateria.cpp \
       Ice.cpp \
       Cure.cpp \
       Character.cpp \
       MateriaSource.cpp

HEADERS = AMateria.hpp Ice.hpp Cure.hpp Character.hpp ICharacter.hpp MateriaSource.hpp IMateriaSource.hpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
