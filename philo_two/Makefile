# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/15 15:00:53 by swquinc           #+#    #+#              #
#    Updated: 2021/03/29 17:23:45 by swquinc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_two

SRCS	= srcs/philo_two.c srcs/actions.c srcs/init.c srcs/utils.c srcs/utils2.c

OBJS	= philo_two.o actions.o init.o utils.o utils2.o

OBJS_D	= objs/philo_two.o objs/actions.o objs/init.o objs/utils.o objs/utils2.o

CC		= gcc -Wall -Wextra -Werror -pthread

INCLUDES = -I includes

.PHONY: all clean fclean re

all: objs $(NAME)

objs:
	mkdir objs

objs/%.o: srcs/%.c
		$(CC) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS_D)
	$(CC) $(OBJS_D) $(INCLUDES) -o $(NAME)

clean:
	/bin/rm -rf objs 
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
