/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:04:23 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:52 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, const char *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	find_start(const char *s1, const char *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && char_in_set(s1[i], set) == 1)
		i++;
	return (i);
}

static unsigned int	find_end(const char *s1, const char *set, unsigned int st)
{
	unsigned int	end;

	end = ft_strlen(s1);
	if (end > 0)
		end--;
	while (end > st && char_in_set(s1[end], set) == 1)
		end--;
	return (end);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*aux;
	unsigned int	i;
	unsigned int	len;

	start = find_start(s1, set);
	end = find_end(s1, set, start);
	if (start >= ft_strlen(s1))
		len = 0;
	else
		len = end - start + 1;
	aux = malloc((len + 1) * sizeof(char));
	if (aux == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		aux[i] = s1[start + i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
