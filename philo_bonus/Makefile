NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

SRC = main_bonus.c utils_bonus.c task_utils_bonus.c colose_semaphores_bonus.c

all = $(NAME)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
