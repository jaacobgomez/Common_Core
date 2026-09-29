/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 19:21:31 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/23 20:33:23 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	long	i;
	long	len;
	int		*range;
	int		iter;

	if (min >= max)
		return (NULL);
	len = (long)max - min;
	range = malloc(len * sizeof(int));
	if (range == NULL)
		return (NULL);
	iter = min;
	i = 0;
	while (i < len)
	{
		range[i] = iter;
		iter++;
		i++;
	}
	return (range);
}
