NAME = minishell

CFLAGS = # -Wall -Wextra -Werror -fsanitize=address -g3

RFLAGS = -lreadline

SRCS =  my_cd.c my_export.c my_echo.c my_env.c my_pwd.c utils.c

OBJ = $(SRCS:.c=.o)
%.o:%.c
	$(CC) $(RFLAG) $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(RFLAG) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
	