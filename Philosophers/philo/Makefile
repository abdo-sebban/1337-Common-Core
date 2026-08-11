MAGENTA  = "\033[1;35m"
RESET    = "\033[0m"
NAME 	 = philo
SRCS 	 = main.c utils.c utils2.c init.c ft_clean.c action.c check_ate_or_death.c init_info.c monitor.c utils3.c
OBJS 	 = $(SRCS:.c=.o)
CC  	 = cc
CFLAGS	 = -Wall -Wextra -Werror

all: $(NAME) ascii

$(NAME): $(OBJS) philo.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

ascii:
	@echo $(MAGENTA)'__________.__    .__.__                            .__                         '$(RESET)
	@echo $(MAGENTA)'\______   \  |__ |__|  |   ____  __________ ______ |  |__   ___________  ______'$(RESET)
	@echo $(MAGENTA)' |     ___/  |  \|  |  |  /  _ \/  ___/  _ \\____ \|  |  \_/ __ \_  __ \/  ___/'$(RESET)
	@echo $(MAGENTA)' |    |   |   Y  \  |  |_(  <_> )___ (  <_> )  |_> >   Y  \  ___/|  | \/\___ \ '$(RESET)
	@echo $(MAGENTA)' |____|   |___|  /__|____/\____/____  >____/|   __/|___|  /\___  >__|  /____  >'$(RESET)
	@echo $(MAGENTA)'               \/                   \/      |__|        \/     \/           \/  '$(RESET)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: ascii clean