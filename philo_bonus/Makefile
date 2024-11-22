CFLAGS = -Wall -Wextra -Werror -O3 -g

NAME = philo_bonus

SRCS = 	main.c		\
		

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(CFLAGS) $(SRCS) -o $(NAME) -pthread
	@echo "... Amazing! I managed to compile $(NAME)"

clean:
	@$(RM) $(OBJ)
	@echo "Objects files removed."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re 
