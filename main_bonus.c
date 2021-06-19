/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:15:27 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/19 19:10:57 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_herdox(t_data data, char **envp)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("/tmp/file", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		get_next_line(0, &line);
		if (!ft_strncmp(data.file1, line, ft_strlen(data.file1)))
		{
			free(line);
			close(fd);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	ft_pipe(data, envp, APND);
	unlink("/tmp/file");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		fd[2];
	int		ret;
	int		fd_in;
	int		fd_out;

	if (argc < 5)
	{
		ft_putendl_fd("Error: Incorrect arguments number!", 2);
		exit(-1);
	}
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 9))
	{
		data = ft_fil_struct(argc - 2, argv + 2);
		ft_herdox(data, envp);
	}
	else
	{
		data = ft_fil_struct(argc - 1, argv + 1);
		ft_pipe(data, envp, WR);
	}
	return (0);
}
