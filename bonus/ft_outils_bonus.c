/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:15:22 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/19 18:25:55 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= (size_t)start)
	{
		return (ft_calloc(1, sizeof(char)));
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && (int)i < (int)size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int		n;
	int		r;
	int		k;

	ptr = malloc(count * size);
	if (ptr)
	{
		n = count * size / sizeof(long);
		r = count * size % sizeof(long);
		k = 0;
		while (n--)
			((long *)ptr)[k++] = 0;
		while (r--)
			((char *)ptr)[k * sizeof(long) + r] = 0;
		return (ptr);
	}
	return (NULL);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
