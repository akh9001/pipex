/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:27:15 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/20 19:45:13 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*last;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
	}
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_cmd	*ft_lstnew(char **args)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = args;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_cmd *lst)
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

void	ft_cmds_free(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		ft_free(current->args);
		free(current);
		current = next;
	}
	*head = NULL;
}
