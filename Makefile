# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 20:40:57 by akhalidy          #+#    #+#              #
#    Updated: 2021/06/14 20:44:36 by akhalidy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAG = -Wall -Wextra -Werror

SRCS = 	ft_cmd_lst.c ft_env_lst.c ft_exce.c ft_outils.c \
		ft_outils_2.c ft_path.c ft_split.c main.c

all:$(NAME)

$(NAME): $(SRCS) 
			@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all
