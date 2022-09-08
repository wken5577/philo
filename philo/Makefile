# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 10:50:54 by hyunkyle          #+#    #+#              #
#    Updated: 2022/09/08 09:36:57 by hyunkyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				= philo.c \
					  each_thread.c \
					  each_thread1.c \
					  ft_atoi.c \
					  philo_log.c \
					  philo_utils.c \
					  philo_utils1.c \
					  philo_utils2.c
					 
					  
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

NAME = philo

$(NAME)	: $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -I philo.h

all	: $(NAME)


clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re	:	
	make fclean 
	make all

.PHONY	:	all clean fclean re
