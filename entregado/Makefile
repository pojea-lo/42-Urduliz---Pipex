# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 07:24:34 by pojea-lo          #+#    #+#              #
#    Updated: 2022/04/05 14:02:03 by pojea-lo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BON = pipex_bonus

MAN = 	pipex.c\
		pipex_utils_0.c\
		pipex_utils_1.c\
		ft_split.c\
		ft_str_0.c\
		ft_str_1.c

MAN_BON =	pipex_bonus.c\
			pipex_bonus_utils_0.c\
			pipex_bonus_utils_1.c\
			pipex_bonus_utils_2.c\
			ft_split_bonus.c\
			ft_str_bonus_0.c\
			ft_str_bonus_1.c

OBJ = $(MAN: .c=.o)

OBJ_BON = $(MAN_BON: .c=.o)

CC = gcc
FLAGS = -Wall -Werror -Wextra
DEB = -g
SAN = -g3 -fsanitize=address

RM = rm -f -r

all: $(NAME)

bonus: $(NAME_BON)

$(NAME): $(OBJ)
	$(CC) -c $(OBJ) $(MAN)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(DEB) #$(SAN)

$(NAME_BON): $(OBJ_BON)
	$(CC) -c $(OBJ_BON) $(MAN_BON)
	$(CC) $(FLAGS) $(OBJ_BON) -o $(NAME_BON) #$(SAN)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME) $(NAME_BON)
	$(RM) *.dSYM

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus

