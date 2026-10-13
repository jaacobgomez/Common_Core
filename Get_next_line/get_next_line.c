/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:41:58 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/13 15:13:25 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	size_t	len;
	char	*newline;

	newline = ft_strchr(stash, '\n');
	if (newline != NULL)
		len = newline - stash + 1;
	else
		len = ft_strlen(stash);
	return (ft_substr(stash, 0, len));
}

static char	*cut_stash(char *stash)
{
	char	*newline;
	char	*rest;

	newline = ft_strchr(stash, '\n');
	if (newline == NULL)
	{
		free(stash);
		return (NULL);
	}
	rest = ft_substr(newline + 1, 0, ft_strlen(newline + 1));
	free(stash);
	if (rest == NULL && rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}
