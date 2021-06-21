/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:06:45 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/21 18:44:13 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_bzero(void *s, size_t n)
{
	int	t;
	int	r;
	int	k;

	if (n)
	{
		t = n / sizeof(long);
		r = n % sizeof(long);
		k = 0;
		while (t--)
			((long *)s)[k++] = 0;
		while (r--)
			((char *)s)[k * sizeof(long) + r] = 0;
	}
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

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	l;

	l = ft_strlen(s1);
	str = (char *)malloc(l + 1);
	if (str)
		ft_strlcpy(str, s1, l + 1);
	return (str);
}
