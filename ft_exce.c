/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exce.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:43:14 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/21 20:30:03 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("Error: Incorrect arguments number!", 2);
		exit(-1);
	}
}

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
			free(slash_cmd);
			ft_free(split);
			return (path);
		}
		free(path);
		i++;
	}
	free(slash_cmd);
	ft_free(split);
	return (NULL);
}

void	ft_continue_exec(char *path, char **envp, char **args)
{
	int	id;
	int	status;

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
	if (path)
		free(path);
}
