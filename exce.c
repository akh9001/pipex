/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:43:14 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/09 12:43:53 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_cmd_path(char *cmd, char *pathenv)
{
	struct stat	buf;
	char		*path;
	char		*pfree;
	char		**split;
	int			i;

	i = 0;
	split = ft_split(pathenv, ':');
	while (split[i])
	{
		path = ft_strjoin("/", cmd);
		pfree = path;
		path = ft_strjoin(split[i], path);
		free(pfree);
		if (!stat(path, &buf))
		{
			ft_free(split);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(split);
	return (NULL);
}

int	ft_path_is_dir(char *args, char **path)
{
	DIR	*dir;
	
	if (!args)
		return (-1);
	dir =  opendir(args);
	if (!dir)
	{
		*path = args;	
		return (1);
	}
	else
		return (0);
}

void	ft_exec_cmd(t_list *envl, char **args)
{
	t_list	*pathenv;
	char	*path;
	char	**envp;
	int		id;
	int		status;
	
	//check if I have a binary file
	if(**args == '/' || !ft_strncmp(*args, "./", 2) || !ft_strncmp(*args, "../", 3))
	{
		if (!ft_path_is_dir(*args, &path))
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(args[0] , 1);
			ft_putendl_fd(": is a directory", 1);
			return;
		}
	}
	// else I have a simple cmd which i should find it s binary file  
	else
	{
		pathenv = ft_find_node(envl, "PATH");
		if (pathenv)
			path = ft_get_cmd_path(args[0], pathenv->value);
		else
			path = NULL;
	}
	printf("%s\n", path);
	if (!path)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(args[0] , 1);
		ft_putendl_fd(": command not found", 1);
	}
	else
	{
		envp = ft_list_to_arr(envl);
		id = fork();
		if (!id)
		{
			execve(path, args, envp);
			ft_putendl_fd(strerror(errno), 1);
			ft_putendl_fd("an arreor has been detected on execve", 1);
			exit(0);
		}
		else
		{
			wait(&status);
			ft_free(envp);
			free(path);
			//printf("status: %d\n", status % 128);
			// if (WIFEXITED(wstatus)) {
			// int statusCode = WEXITSTATUS(wstatus);
			// if (statusCode == 0) {
			//     printf("Success\n");
			// } else {
			//     printf("Failure with status code %d\n", statusCode);
			// }
		// }
		}
	}
}