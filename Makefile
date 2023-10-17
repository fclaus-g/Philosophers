# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:01:55 by fclaus-g          #+#    #+#              #
#    Updated: 2023/10/17 14:04:44 by fclaus-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
RM = rm -f

SRC = src/main.c src/init.c src/routine.c src/actions.c src/time.c \
src/print.c src/utils.c src/monitoring.c src/end.c src/check_n_set.c
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33m Compiling program Philosophers\n"
	@$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)
	@echo "\033[0;32mThe Philosophers are on the table\n\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re