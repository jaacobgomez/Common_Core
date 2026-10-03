/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:51:32 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/02 22:57:24 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	word_len(const char *s, char c)
{
	unsigned int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static unsigned int	count_words(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;
	unsigned int	inside;

	i = 0;
	count = 0;
	inside = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && inside == 0)
		{
			inside = 1;
			count++;
		}
		else if (s[i] == c)
			inside = 0;
		i++;
	}
	return (count);
}

static char	*copy_words(const char *s, char c)
{
	unsigned int	len;
	unsigned int	i;
	char			*aux;

	len = word_len(s, c);
	aux = malloc((len + 1) * sizeof(char));
	if (aux == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		aux[i] = s[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}

static int	fill_words(char **arr, const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			arr[j] = copy_words(s + i, c);
			if (arr[j] == NULL)
				return (0);
			i = i + word_len(s + i, c);
			j++;
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char			**arr;
	unsigned int	words;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	if (fill_words(arr, s, c) == 0)
	{
		i = 0;
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		return (NULL);
	}
	return (arr);
}
