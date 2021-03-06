# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/16 11:55:49 by jbaringo          #+#    #+#              #
#    Updated: 2021/09/30 11:08:56 by jbaringo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo
CC =	gcc
FLAGS = -c -pthread -Wall -Wextra -Werror
OBJS =	$(SRCS:.c=.o)
SRCS =	srcs/main.c srcs/utils.c srcs/threads.c srcs/main_thread.c srcs/check_arguments.c

philo: $(SRCS)
	$(CC) $(FLAGS) $(SRCS)
	mkdir -p srcs/obj
	mv *.o srcs/obj
	gcc -pthread -o $(NAME) srcs/obj/*.o

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f srcs/obj/*.o
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
