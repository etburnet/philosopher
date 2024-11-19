# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 09:11:20 by eburnet           #+#    #+#              #
#    Updated: 2024/08/28 09:11:20 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philos
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = main.c philos_utils.c thread.c monitor.c thread_utils.c 
OBJS = $(SRCS:.c=.o)
HEADERS = philos.h

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re