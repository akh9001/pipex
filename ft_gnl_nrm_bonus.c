/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_nrm_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:29:32 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/22 15:47:15 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_tmp(char *tmp, char **line, char **rest, char *buf)
{
	char	*tp;

	*tmp = '\0';
	*line = ft_strdup(*rest);
	if (!*line)
		return (-1);
	tp = *rest;
	*rest = ft_strdup(tmp + 1);
	if (!*rest)
		return (-1);
	ft_safe_free(tp);
	ft_safe_free(buf);
	return (1);
}
