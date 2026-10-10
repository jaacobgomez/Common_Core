/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:03:13 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/02 22:53:23 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	join_strings(char *aux, const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		aux[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		aux[i] = s2[j];
		i++;
		j++;
	}
	aux[i] = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*aux;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	aux = malloc((len1 + len2 + 1) * sizeof(char));
	if (aux == NULL)
		return (NULL);
	join_strings(aux, s1, s2);
	return (aux);
}
