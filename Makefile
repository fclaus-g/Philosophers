# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: usuario42 <usuario42@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:01:55 by usuario42         #+#    #+#              #
#    Updated: 2023/08/09 09:25:42 by usuario42        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRC = src/main.c src/init.c src/actions.c
OBJ = $(SRC:.c=.o)

LIBFT = ./libft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS)  $(OBJ) $(LIBFT)/libft.a -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT)
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)
re: fclean all

.PHONY: all clean fclean re