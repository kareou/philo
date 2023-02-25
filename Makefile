NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = main.c utils.c task_utils.c

all = $(NAME)

NAME : 
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm *.c

fclean : clean
		rm $(NAME)

re : fclean 
	all

phony : clean fclean re