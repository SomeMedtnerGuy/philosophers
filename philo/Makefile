# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 15:06:49 by ndo-vale          #+#    #+#              #
#    Updated: 2024/06/17 18:56:55 by ndo-vale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g 
RM	= rm -rf

SRC_DIR	= src/
SRCS		= $(addprefix $(SRC_DIR), main.c helpers.c helpers2.c \
		  initializers.c freers.c actions.c)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
