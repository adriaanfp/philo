CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

NAME = philo

SRCS = philo.c philo_utils.c philo_utils2.c atol.c death_monitor.c routine.c

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "$(GREEN)Linking objects to create executable $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo -e "$(GREEN)Build completed successfully!$(RESET)"

%.o: %.c
	@echo -e "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	rm -f $(OBJS)

fclean: clean
	@echo -e "$(RED)Removing executable...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re