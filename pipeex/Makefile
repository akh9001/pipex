# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 20:40:57 by akhalidy          #+#    #+#              #
#    Updated: 2021/06/21 18:59:44 by akhalidy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAG = -Wall -Wextra -Werror

SRCS = 	ft_cmd_lst.c ft_env_lst.c ft_exce.c ft_outils.c \
		ft_outils_2.c ft_path.c ft_split.c main.c ft_pipe.c

SRCSB =	ft_cmd_lst_bonus.c \
		ft_env_lst_bonus.c \
		ft_exce_bonus.c \
		ft_outils_2_bonus.c \
		ft_outils_bonus.c \
		ft_path_bonus.c \
		ft_pipe_bonus.c \
		ft_split_bonus.c \
		main_bonus.c \

all:$(NAME)

$(NAME): $(SRCS) 
			@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus:
	@$(CC) $(CFLAGS) $(SRCSB) -o $(NAME)