/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:51:45 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/11 21:33:42 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data  ft_fil_struct(int argc, char **argv)
{
	t_data	data;
	char	**split;
	int		i;

	i = 0;
	data.cmds = NULL;
	argc = argc - 2;
	data.file1 = *argv;
	while(++i <= argc)
	{
		split = ft_split(argv[i], ' ');	
		ft_lstadd_back(&data.cmds, ft_lstnew(split));
	}
	data.file2 = argv[i];
	return(data);
}

void	ft_print_cmd(t_data data)
{
	t_cmd	*lst;
	int		i;
	int		j;
	
	lst = data.cmds;
	printf("f1 : %s\n", data.file1);
	j = 0;
	while(lst)
	{
		i = 0;
		while (lst->args[i])
		{
			// printf("lst : %p\n", lst);
			printf("cmd %d: %s\n", j, lst->args[i]);
			i++;
		}
		j++;
		lst = lst->next;
	}
	printf("f2 : %s\n", data.file2);
}

int		ft_print_error(char *cmd, char *path)
{
	ft_putstr_fd(cmd, 1);
	if (path)
	{
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(path, 1);	
	}
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;
	int		fd_in;
	int		ret;

	data = ft_fil_struct(argc - 1, argv + 1);
	fd_in = open(data.file1, O_RDONLY);
	printf("%d\n", fd_in);
	if (fd_in > 0)
		ret = read(fd_in, NULL, 0);
	if (fd_in == -1 || ret == -1)
	{
		ft_print_error(data.file1, NULL);
		exit(-1);
	}
	ft_print_cmd(data);
	return(0);
}