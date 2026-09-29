/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:02:30 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:29 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*aux_dest;
	const unsigned char	*aux_src;

	i = 0;
	aux_dest = (unsigned char *)dest;
	aux_src = (const unsigned char *)src;
	if (aux_dest < aux_src)
	{
		while (i < n)
		{
			aux_dest[i] = aux_src[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			aux_dest[i] = aux_src[i];
		}
	}
	return (dest);
}
