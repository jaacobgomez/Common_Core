/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:03:30 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/02 23:25:23 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*aux;

	if (s == NULL || f == NULL)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	aux = malloc((len + 1) * sizeof(char));
	if (aux == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		aux[i] = f(i, s[i]);
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
