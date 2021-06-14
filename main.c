/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:51:45 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/14 20:26:42 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	ft_fil_struct(int argc, char **argv)
{
	t_data	data;
	char	**split;
	int		i;

	i = 0;
	data.cmds = NULL;
	argc = argc - 2;
	data.file1 = *argv;
	while (++i <= argc)
	{
		split = ft_split(argv[i], ' ');
		ft_lstadd_back(&data.cmds, ft_lstnew(split));
	}
	data.file2 = argv[i];
	return (data);
}

int	ft_print_error(char *cmd, char *path)
{
	ft_putstr_fd(cmd, 2);
	if (path)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_is_file(int *fd, char *file, int type)
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
		exit(-1);
	}
}

void	ft_process(t_cmd *cmds, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		if (cmds->in)
		{
			dup2(cmds->in, 0);
			close(cmds->in);
		}
		if (cmds->out != 1)
		{
			dup2(cmds->out, 1);
			close(cmds->out);
		}
		ft_exec_cmd(envp, cmds->args);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		fd[2];
	int		ret;
	int		fd_in;
	int		fd_out;

	check_args(argc);
	ret = pipe(fd);
	if (ret < 0)
		ft_print_error("Error :", NULL);
	data = ft_fil_struct(argc - 1, argv + 1);
	ft_is_file(&fd_in, data.file1, RD);
	data.cmds->in = fd_in;
	data.cmds->out = fd[1];
	ft_is_file(&fd_out, data.file2, WR);
	data.cmds->next->in = fd[0];
	data.cmds->next->out = fd_out;
	ft_process(data.cmds, envp);
	close(fd[1]);
	ft_process(data.cmds->next, envp);
	close(fd[0]);
	return (0);
}
