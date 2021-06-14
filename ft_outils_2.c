/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:53:25 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/14 19:55:03 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!s)
		return ;
	len = ft_strlen(s);
	while (i < len)
		ft_putchar_fd(s[i++], fd);
}

static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int	i;
	int	l;
	int	max;

	if (!dst && size == 0)
		return (ft_strlen(src));
	l = (int)ft_strlen(dst);
	max = (int)size - l - 1;
	i = 0;
	while (src[i] && i < max)
	{
		dst[l + i] = src[i];
		i++;
	}
	if (max > 0)
		dst[l + i] = '\0';
	return (ft_min((size_t)l, size) + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (str);
}
