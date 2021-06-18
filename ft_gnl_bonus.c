/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:29:32 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/18 20:31:06 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#define BUFFER_SIZE 1000

char	*ft_strjoin1(char *s1, char const *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = (char*)malloc((ls1 + ls2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ls1 + 1);
	ft_strlcpy(str + ls1, s2, ls2 + 1);
	free(s1);
	return (str);
}

int		checkrest(char **rest, char **line)
{
	char *tp;
	char *tmp;

	if (*rest)
	{
		if ((tmp = ft_strchr(*rest, '\n')))
		{
			*tmp = '\0';
			if (!(*line = ft_strdup(*rest)))
				return (-1);
			tp = *rest;
			if (!(*rest = ft_strdup(tmp + 1)))
				return (-1);
			free(tp);
			return (1);
		}
	}
	else if (!(*rest = ft_strdup("")))
		return (-1);
	return (0);
}

int		getn(int fd, char **rest, char *buf, char **line)
{
	int		r;
	char	*tmp;
	char	*tp;

	while ((r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (!(*rest = ft_strjoin1(*rest, buf)))
			return (-1);
		if ((tmp = ft_strchr(*rest, '\n')))
		{
			*tmp = '\0';
			if (!(*line = ft_strdup(*rest)))
				return (-1);
			tp = *rest;
			if (!(*rest = ft_strdup(tmp + 1)))
				return (-1);
			free(tp);
			free(buf);
			return (1);
		}
		ft_bzero(buf, BUFFER_SIZE);
	}
	free(buf);
	return (r);
}

int		get_next_line(int fd, char **line)
{
	int			rd;
	static char *rest[1024];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 0 || !line)
		return (-1);
	if ((rd = checkrest(rest + fd, line)))
		return (rd);
	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	rd = getn(fd, rest + fd, buf, line);
	if (rd == 1)
		return (1);
	if (*(rest + fd) && !rd)
	{
		if (!(*line = ft_strdup(*(rest + fd))))
			return (-1);
		free(*(rest + fd));
		*(rest + fd) = NULL;
	}
	return (rd);
}
