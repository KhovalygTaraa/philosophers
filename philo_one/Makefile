# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/15 15:00:53 by swquinc           #+#    #+#              #
#    Updated: 2021/03/22 14:34:47 by swquinc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_one

SRCS	= srcs/philo_one.c srcs/actions.c srcs/init.c srcs/utils.c

OBJS	= philo_one.o actions.o init.o utils.o

CC		= gcc -Wall -Wextra -Werror

INCLUDES = -I includes

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	mkdir objs
	$(CC) $(SRCS) $(INCLUDES) -c
	mv $(OBJS) objs/
	$(CC) $(SRCS) $(INCLUDES) -o $(NAME)

clean:
	/bin/rm -rf objs

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
