# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 21:36:01 by lucaslefran       #+#    #+#              #
#    Updated: 2021/04/28 14:22:18 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_two
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

SRCS		=	main.c utils.c init.c libft.c threads.c
OBJS		=	$(SRCS:.c=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS) -lpthread

%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<
# for creating .o with flags

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
