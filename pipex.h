/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:52:40 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/11 21:06:58 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>

typedef struct		s_cmd
{
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct  	s_data
{
	char			*file1;
	char			*file2;
	t_cmd			*cmds;
}               	t_data;

// list functions
t_cmd				*ft_lstnew(char **args);
void				ft_lstadd_back(t_cmd **alst, t_cmd *new);
int					ft_lstsize(t_cmd *lst);
t_cmd				*ft_lstlast(t_cmd *lst);

//help functions
size_t				ft_strlen(const char *str);
char				**ft_split(char const *s, char c);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
#endif