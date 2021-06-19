/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exce_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:43:14 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/19 18:38:08 by akhalidy         ###   ########.fr       */
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

	if (!path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
	{
		id = fork();
		if (!id)
		{
			execve(path, args, envp);
			ft_putendl_fd(strerror(errno), 2);
			exit(0);
		}
		else
		{
			wait(NULL);
			free(path);
		}
	}
}

void	ft_exec_cmd(char **envp, char **args)
{
	t_list	*pathenv;
	t_list	*envl;
	char	*path;

	envl = ft_arr_to_list(envp);
	path = NULL;
	if (**args == '/' || !ft_strncmp(*args, "./", 2)
		|| !ft_strncmp(*args, "../", 3))
		path = *args;
	else
	{
		pathenv = ft_find_node(envl, "PATH");
		if (pathenv)
			path = ft_get_cmd_path(args[0], pathenv->value);
		else
			path = ft_get_cmd_path(args[0], ".");
	}
	ft_continue_exec(path, envp, args);
}
