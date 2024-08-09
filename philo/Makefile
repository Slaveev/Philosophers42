NAME = philo
CC = cc
CFLAGS = -Wextra -Werror -Wall -std=c99 -g

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils1.c $(SRC_DIR)/cleanup.c $(SRC_DIR)/init.c $(SRC_DIR)/monitoring.c $(SRC_DIR)/routine.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning"
	@rm -f $(SRC_DIR)/*.o

fclean: clean
	@echo "Full cleaning"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
