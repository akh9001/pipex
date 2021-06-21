/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 13:52:51 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/20 19:35:28 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_envl_add_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			last = ft_envl_last(*alst);
			last->next = new;
		}
	}
}

t_list	*ft_envl_last(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_list	*ft_envl_new(char *env, char *value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->env = env;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_envl_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lst_free(t_list **head)
{
	t_list	*current;
	t_list	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->env);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}
