/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:29:32 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/22 15:47:15 by akhalidy         ###   ########.fr       */
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
	str = (char *)malloc((ls1 + ls2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ls1 + 1);
	ft_strlcpy(str + ls1, s2, ls2 + 1);
	ft_safe_free(s1);
	return (str);
}

int	checkrest(char **rest, char **line)
{
	char	*tp;
	char	*tmp;

	if (*rest)
	{
		tmp = ft_strchr(*rest, '\n');
		if (tmp)
		{
			*tmp = '\0';
			*line = ft_strdup(*rest);
			if (!*line)
				return (-1);
			tp = *rest;
			*rest = ft_strdup(tmp + 1);
			if (!*rest)
				return (-1);
			free(tp);
			return (1);
		}
	}
	else
		*rest = ft_strdup("");
	return (0);
}

int	getn(int fd, char **rest, char *buf, char **line)
{
	int		r;
	char	*tmp;
	char	*tp;

	r = read(fd, buf, BUFFER_SIZE);
	while (r > 0)
	{
		buf[r] = '\0';
		*rest = ft_strjoin1(*rest, buf);
		if (!*rest)
			return (-1);
		tmp = ft_strchr(*rest, '\n');
		if (tmp)
			return (ft_check_tmp(tmp, line, rest, buf));
		ft_bzero(buf, BUFFER_SIZE);
		r = read(fd, buf, BUFFER_SIZE);
	}
	ft_safe_free(buf);
	return (r);
}

int	get_next_line(int fd, char **line)
{
	int			rd;
	static char	*rest[1024];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 0 || !line)
		return (-1);
	rd = checkrest(rest + fd, line);
	if (rd)
		return (rd);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (-1);
	rd = getn(fd, rest + fd, buf, line);
	if (rd == 1)
		return (1);
	if (*(rest + fd) && !rd)
	{
		*line = ft_strdup(*(rest + fd));
		if (!*line)
			return (-1);
		ft_safe_free(*(rest + fd));
		*(rest + fd) = NULL;
	}
	return (rd);
}
