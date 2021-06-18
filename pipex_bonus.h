/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:16:46 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/18 22:02:17 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define RD		0
# define WR		1
# define APND	2
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "pipex.h"

// typedef struct s_cmd
// {
// 	char			**args;
// 	int				in;
// 	int				out;
// 	struct s_cmd	*next;
// }					t_cmd;

// typedef struct s_data
// {
// 	char			*file1;
// 	char			*file2;
// 	t_cmd			*cmds;
// }					t_data;

// typedef struct s_list
// {
// 	char			*env;
// 	char			*value;
// 	struct s_list	*next;
// }					t_list;

void	ft_pipe(t_data data, t_list *envl, int wr, int in);
int		get_next_line(int fd, char **line);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
#endif