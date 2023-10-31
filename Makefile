# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 16:27:40 by aalkaisi          #+#    #+#              #
#    Updated: 2023/10/17 19:24:15 by aalkaisi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c ft_split.c extra.c

OBJ = $(SRC:.c=.o)

CC = cc

NAME = minishell

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJ)
	
fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re