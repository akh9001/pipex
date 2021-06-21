/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:52:40 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/21 18:27:26 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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

typedef struct s_cmd
{
	char			**args;
	int				pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			*file1;
	char			*file2;
	t_cmd			*cmds;
}					t_data;

typedef struct s_list
{
	char			*env;
	char			*value;
	struct s_list	*next;
}					t_list;

typedef struct s_help
{
	size_t			end;
	size_t			start;
	size_t			i;
	char			**ptr;
}					t_help;

t_cmd				*ft_lstnew(char **args);
void				ft_lstadd_back(t_cmd **alst, t_cmd *new);
int					ft_lstsize(t_cmd *lst);
t_cmd				*ft_lstlast(t_cmd *lst);
void				ft_envl_add_back(t_list **alst, t_list *new);
t_list				*ft_envl_last(t_list *lst);
t_list				*ft_envl_new(char *env, char *value);
int					ft_envl_size(t_list *lst);
size_t				ft_strlen(const char *str);
char				**ft_split(char const *s, char c);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putendl_fd(char *s, int fd);
char				**ft_free(char **ptr);
t_list				*ft_arr_to_list(char **str);
t_list				*ft_find_node(t_list *lst, char *content);
char				**ft_list_to_arr(t_list *lst);
void				check_args(int argc);
void				ft_is_file(int *fd, char *file, int type, int option);
void				ft_exec_cmd(char **envp, char **args);
char				*ft_strdup(const char *s1);
void				ft_lst_free(t_list **head);
void				ft_cmds_free(t_cmd **head);
int					ft_pipe(t_data data, char **envp, int wr);
int					ft_print_error(char *cmd, char *path);

#endif