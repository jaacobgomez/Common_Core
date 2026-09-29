/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:02:36 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:24 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux_s;

	i = 0;
	aux_s = (unsigned char *)s;
	while (i < n)
	{
		aux_s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
