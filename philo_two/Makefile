# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/15 15:00:53 by swquinc           #+#    #+#              #
#    Updated: 2021/03/22 15:51:35 by swquinc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_two

SRCS	= srcs/philo_two.c srcs/actions.c srcs/init.c srcs/utils.c

OBJS	= philo_two.o actions.o init.o utils.o

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
