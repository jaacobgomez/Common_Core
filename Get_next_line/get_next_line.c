/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:41:58 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/14 01:29:14 by jacgomez         ###   ########.fr       */
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
	if (rest != NULL && rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

static char	*free_all(char *a, char *b)
{
	free(a);
	free(b);
	return (NULL);
}

static char	*can_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes;

	if (ft_strchr(stash, '\n') != NULL)
		return (stash);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (free_all(stash, buf));
	bytes = 1;
	while (bytes > 0 && ft_strchr(stash, '\n') == NULL)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		stash = ft_strjoin(stash, buf);
		if (stash == NULL)
			break ;
	}
	if (bytes < 0)
		return (free_all(stash, buf));
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = can_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = extract_line(stash);
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = cut_stash(stash);
	return (line);
}
