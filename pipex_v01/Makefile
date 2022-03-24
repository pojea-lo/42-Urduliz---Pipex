NAME = pipex

MAN = 	pipex.c\
		ft_split.c\
		ft_str.c

OBJ = $(MAN: .c=.o)

CC = gcc
FLAGS = -Wall -Werror -Wextra
SAN = -g3 -fsanitize=address

RM = rm -f -r

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -c $(OBJ) $(MAN)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(SAN)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME) 
	$(RM) *.dSYM

re: fclean all

.PHONY: all clean fclean re

