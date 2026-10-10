/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:02:19 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:12 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux;

	i = 0;
	aux = (unsigned char *)s;
	while (n > 0)
	{
		if (aux[i] == (unsigned char)c)
			return (&aux[i]);
		i++;
		n--;
	}
	return (NULL);
}
