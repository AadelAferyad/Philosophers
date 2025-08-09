NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c parser.c utils.c get_struct_data.c init_data.c dining.c routine.c routine_util.c philo_check.c 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
