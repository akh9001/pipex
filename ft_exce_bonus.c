/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exce_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:43:14 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/22 16:15:52 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_get_cmd_path(char *cmd, char *pathenv)
{
	char		*path;
	char		*slash_cmd;
	char		**split;
	int			i;

	i = 0;
	if (!*cmd)
		return (NULL);
	split = ft_split(pathenv, ':');
	slash_cmd = ft_strjoin("/", cmd);
	while (split[i])
	{
		path = ft_strjoin(split[i], slash_cmd);
		if (open(path, O_RDONLY) > 0)
		{
			ft_safe_free(slash_cmd);
			ft_free(split);
			return (path);
		}
		ft_safe_free(path);
		i++;
	}
	ft_safe_free(slash_cmd);
	ft_free(split);
	return (NULL);
}

void	ft_continue_exec(char *path, char **envp, char **args)
{
	int	id;

	if (!path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else
	{
		execve(path, args, envp);
		ft_putendl_fd(strerror(errno), 2);
		if (errno == 21)
			exit(1);
		if (errno == 13)
			exit(126);
		if (errno == 2)
			exit(127);
	}
}

char	*ft_search_path(char **envp, char **args)
{
	t_list	*pathenv;
	t_list	*envl;
	char	*path;

	path = NULL;
	envl = ft_arr_to_list(envp);
	pathenv = ft_find_node(envl, "PATH");
	if (pathenv)
		path = ft_get_cmd_path(args[0], pathenv->value);
	else
		path = ft_get_cmd_path(args[0], ".");
	ft_lst_free(&envl);
	return (path);
}

void	ft_exec_cmd(char **envp, char **args)
{
	char	*path;
	int		k;

	path = NULL;
	k = 99;
	if (**args == '/' || !ft_strncmp(*args, "./", 2)
		|| !ft_strncmp(*args, "../", 3))
	{
		path = ft_strdup(*args);
		if (read(open(path, O_RDONLY), NULL, 0) < 0)
		{
			if (errno == 21)
			{
				ft_putstr_fd(path, 2);
				ft_putendl_fd(" : is a directory", 2);
				k = 0;
			}
		}
	}
	else
		path = ft_search_path(envp, args);
	if (k)
		ft_continue_exec(path, envp, args);
	ft_safe_free(path);
}

void	ft_safe_free(void *str)
{
	if (str)
		free(str);
	str = NULL;
}
