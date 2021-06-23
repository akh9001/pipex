/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 13:51:17 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/22 15:47:15 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_list_to_arr(t_list *lst)
{
	t_list	*tmp;
	char	**str;
	char	*pfree;
	int		i;

	i = 0;
	tmp = lst;
	str = (char **)malloc((ft_envl_size(lst) + 1) * sizeof(char *));
	while (lst)
	{
		str[i] = ft_strjoin(lst->env, "=");
		pfree = str[i];
		str[i] = ft_strjoin(str[i], lst->value);
		free(pfree);
		lst = lst->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

t_list	*ft_arr_to_list(char **str)
{
	t_list	*lst;
	char	**split;
	int		i;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		split = ft_split(str[i], '=');
		ft_envl_add_back(&lst, ft_envl_new(split[0], split[1]));
		free(split);
		i++;
	}
	return (lst);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (-404);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((*str1 || *str2) && n)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
		n--;
	}
	return (0);
}

t_list	*ft_find_node(t_list *lst, char *content)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env, content, ft_strlen(content) + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
