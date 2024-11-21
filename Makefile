CFLAGS = -Wall -Wextra -Werror -O3

NAME = philo

BONUS = checker

SRCS = ./sources/main.c					\
		./sources/init.c				\
		./sources/utils_one.c				\
		./sources/utils_two.c			\
		./sources/threads_one.c				\
		./sources/threads_two.c	\


BONUS_SRCS = ./main.c

all: $(NAME)



$(NAME): $(SRCS)
	@cc $(CFLAGS) $(SRCS) -o $(NAME) -pthread
	@echo "... Amazing! I managed to compile philo"

bonus: $(SRCS) $(BONUS_SRCS)
	@cc $(CFLAGS) $(SRCS) $(BONUS_SRCS) -o $(BONUS) 
	@echo "... Amazing! I managed to compile the checker"

clean:
	@$(RM) $(OBJ)
	@echo "Objects files removed."

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS)
	@echo "$(NAME) and $(BONUS) removed."

re: fclean all

.PHONY: all clean fclean re bonus
