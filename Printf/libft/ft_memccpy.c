/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:02:13 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:47 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*aux_dest;
	char	*aux_src;

	aux_dest = (char *)dest;
	aux_src = (char *)src;
	i = 0;
	while (n > 0)
	{
		aux_dest[i] = aux_src[i];
		if (aux_src[i] == (char)c)
			return (aux_dest + i + 1);
		i++;
		n--;
	}
	return (NULL);
}
