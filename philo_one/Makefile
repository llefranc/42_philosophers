# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/13 21:36:01 by lucaslefran       #+#    #+#              #
#    Updated: 2020/11/15 13:13:05 by lucaslefran      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_one
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address

SRCS		=	main.c utils.c init.c libft.c

OBJS		=	$(SRCS:.c=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) -o $(NAME) $(FLAGS) $(OBJS)

%.o		:	%.c
			$(CC) $(FLAGS) -o $@ -c $<
# for creating .o with flags

clean	:	
				rm -rf $(OBJS)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
