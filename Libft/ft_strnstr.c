/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:03:37 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/28 16:20:21 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*find == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while ((i + j) < n && str[i + j] == find[j] && find[j] != '\0')
			j++;
		if (find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
