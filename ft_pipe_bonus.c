/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:06:45 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/18 22:06:33 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	ft_fork_pipe(int *io, char **args, t_list *envl, int *pid)
{
	*pid = fork();
	if (!*pid)
	{
		dup2(io[1], 1);
		dup2(io[0], 0);
		if (io[0] != 0)
			close(io[0]);
		if (io[1] != 1)
			close(io[1]);
		close(io[2]);
		ft_launch_exec(args, envl);
		exit(0);
	}
	if (io[0] != 0)
		close(io[0]);
	if (io[1] != 1)
		close(io[1]);
}

// void	ft_set_io(int *fd_io, int *io, int out)
// {
// 	if (fd_io[0] != -18)
// 		io[0] = fd_io[0];
// 	if (fd_io[1] != -18)
// 		io[1] = fd_io[1];
// 	else
// 		io[1] = out;
// }

void	ft_bzero(void *s, size_t n)
{
	int t;
	int r;
	int k;

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


void	ft_pipe(t_data data, t_list *envl, int wr, int in)
{
	int		fd[2];
	int		io[3];
	int		status;
	t_cmd	*lst;
	// int		fd_io[2];

	if (wr == WR)
		ft_is_file(&io[0], data.file1, RD);
	else
		io[0] = in;
	//io[0] = fd[0];
	lst = data.cmds;
	while (lst->next)
	{
		pipe(fd);
		io[2] = fd[0];
		io[1] = fd[1];
		// ft_redirect(lst->file, &fd_io[0], &fd_io[1]);
		// ft_set_io(fd_io, io, fd[1]);
		ft_fork_pipe(io, lst->args, envl, &lst->pid);
		close(fd[1]);
		io[0] = io[2];
		lst = lst->next;
	}
	// ft_redirect(lst->file, &fd_io[0], &fd_io[1]);
	ft_is_file(&io[1], data.file2, wr);
//	ft_set_io(fd_io, io, 1);
	// if (lst)
	ft_fork_pipe(io, lst->args, envl, &lst->pid);
	while (data.cmds)
	{
		waitpid(data.cmds->pid, &status, 0);
		data.cmds = data.cmds->next;
	}
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char*)s;
	if ((char)c == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
