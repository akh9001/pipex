/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:44:47 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/11 16:15:45 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		wordcounter(const char *str, char c)
{
	int count;
	int i;

	if (!*str)
		return (0);
	count = 0;
	i = 1;
	if (str[0] != c)
		count++;
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

int		ft_split_num(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_free(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	end;
	size_t	start;
	size_t	i;
	char	**ptr;

	if (!s)
		return (NULL);
	if (!(ptr = (char **)malloc((wordcounter(s, c) + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] != c && s[end])
			end++;
		if (s[end - 1] != c)
			if (!(ptr[i++] = ft_substr(s, start, end - start)))
				return (ft_free(ptr));
	}
	ptr[i] = NULL;
	return (ptr);
}
