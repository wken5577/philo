# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 10:50:54 by hyunkyle          #+#    #+#              #
#    Updated: 2022/09/08 19:07:59 by hyunkyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				= philo_bonus.c \
					  each_philos_bonus.c \
					  ft_atoi_bonus.c \
					  philo_log_bonus.c \
					  philo_utils_bonus.c \
					  philo_utils_bonus1.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

NAME = philo_bonus

$(NAME)	: $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -I philo_bonus.h

all	: $(NAME)

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re	:	
	make fclean 
	make all

.PHONY	:	all clean fclean re
