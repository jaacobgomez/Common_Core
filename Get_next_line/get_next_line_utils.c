/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:10:02 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/10 22:41:34 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*aux;

	i = 0;
	if (s == NULL)
		return (NULL);
	aux = (char *)s;
	while (aux[i] != '\0')
	{
		if (aux[i] == (char)c)
			return (aux + i);
		i++;
	}
	if ((char)c == '\0')
		return (aux + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*aux;
	size_t	i;
	size_t	j;

	aux = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (aux == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
	{
		aux[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		aux[i + j] = s2[j];
		j++;
	}
	aux[i + j] = '\0';
	free(s1);
	return (aux);
}

char	*ft_substr(const char *s, size_t start, size_t len)
{
	char	*aux;
	size_t	i;

	aux = (char *)malloc((len + 1) * sizeof(char));
	if (aux == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		aux[i] = s[start + i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
