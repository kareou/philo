NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c task_utils.c

all = $(NAME)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	$(RM) *.o

fclean : clean
	$(RM) $(NAME)

re : fclean all
