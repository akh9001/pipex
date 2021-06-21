/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:44:47 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/21 18:27:55 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wordcounter(const char *str, char c)
{
	int	count;
	int	i;

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

int	ft_split_num(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	t_help	hlp;

	if (!s)
		return (NULL);
	hlp.ptr = (char **)malloc((wordcounter(s, c) + 1) * sizeof(char *));
	if (!hlp.ptr)
		return (NULL);
	hlp.i = 0;
	hlp.end = 0;
	while (s[hlp.end])
	{
		while (s[hlp.end] == c)
			hlp.end++;
		hlp.start = hlp.end;
		while (s[hlp.end] != c && s[hlp.end])
			hlp.end++;
		if (s[hlp.end - 1] != c)
		{
			hlp.ptr[hlp.i++] = ft_substr(s, hlp.start, hlp.end - hlp.start);
			if (!hlp.ptr)
				return (ft_free(hlp.ptr));
		}
	}
	hlp.ptr[hlp.i] = NULL;
	return (hlp.ptr);
}
