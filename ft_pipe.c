/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 18:03:51 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/21 18:41:10 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_is_file(int *fd, char *file, int type, int option)
{
	if (type == RD)
		*fd = open(file, O_RDONLY);
	else if (type == WR)
		*fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == APND)
		*fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (*fd == -1)
	{
		ft_print_error(file, NULL);
		if (option)
			exit(1);
	}
}

void	ft_fork_pipe(int *io, char **args, char **envp, int *pid)
{
	*pid = fork();
	if (!*pid && io[0] != -1)
	{
		dup2(io[1], 1);
		dup2(io[0], 0);
		if (io[0] != 0)
			close(io[0]);
		if (io[1] != 1)
			close(io[1]);
		close(io[2]);
		ft_exec_cmd(envp, args);
	}
	if (io[0] != 0)
		close(io[0]);
	if (io[1] != 1)
		close(io[1]);
}

int	ft_wait_loop(t_cmd	*cmds)
{
	int	status;

	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		cmds = cmds->next;
	}
	return (WEXITSTATUS(status));
}

int	ft_pipe(t_data data, char **envp, int wr)
{
	int		fd[2];
	int		io[3];
	char	*str;
	t_cmd	*lst;

	if (wr == WR)
		ft_is_file(&io[0], data.file1, RD, 0);
	else
		io[0] = open("/tmp/file", O_RDONLY, 0644);
	lst = data.cmds;
	while (lst->next)
	{
		pipe(fd);
		io[2] = fd[0];
		io[1] = fd[1];
		ft_fork_pipe(io, lst->args, envp, &lst->pid);
		close(fd[1]);
		io[0] = io[2];
		lst = lst->next;
	}
	ft_is_file(&io[1], data.file2, wr, 1);
	ft_fork_pipe(io, lst->args, envp, &lst->pid);
	return (ft_wait_loop(data.cmds));
}
