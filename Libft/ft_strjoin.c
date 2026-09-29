/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:03:13 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:39 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*aux;
	unsigned int	iter_aux;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	aux = malloc((i + j + 1) * sizeof(char));
	if (aux == NULL)
		return (NULL);
	iter_aux = 0;
	while (s1[iter_aux] != '\0')
	{
		aux[iter_aux] = s1[iter_aux];
		iter_aux++;
	}
	iter_aux = 0;
	while (s2[iter_aux] != '\0')
	{
		aux[i] = s2[iter_aux];
		i++;
		iter_aux++;
	}
	aux[i] = '\0';
	return (aux);
}
