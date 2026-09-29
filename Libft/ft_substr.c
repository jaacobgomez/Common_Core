/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:41:22 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/24 18:00:53 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_substr(void)
{
	char	*str;

	str = malloc(1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			len_str;
	unsigned int	i;
	char			*str;
	unsigned int	j;

	if (start >= (unsigned int)ft_strlen(s))
		return (empty_substr());
	i = start;
	len_str = 0;
	while (s[i] != '\0' && len_str < len)
	{
		i++;
		len_str++;
	}
	str = malloc((len_str + 1) * sizeof (char));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s[j + start] != '\0' && j < len_str)
	{
		str[j] = s[j + start];
		j++;
	}
	str[j] = '\0';
	return (str);
}
