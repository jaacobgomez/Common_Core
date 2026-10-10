/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:02:10 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/29 14:36:25 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_num(int n)
{
	int	i;

	i = 1;
	n = n / 10;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static int	get_len(int n)
{
	int	len;

	len = len_num(n) + 1;
	if (n < 0)
		len = len + 1;
	return (len);
}

static int	fill_digits(char *aux, long nb, int i)
{
	if (nb < 0)
		nb = -nb;
	if (nb == 0)
	{
		aux[i] = '0';
		i--;
	}
	while (nb != 0)
	{
		aux[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*aux;
	int		i;
	int		total;

	total = get_len(n);
	aux = malloc(total);
	if (aux == NULL)
		return (NULL);
	i = total - 1;
	aux[i] = '\0';
	i--;
	i = fill_digits(aux, (long)n, i);
	if (n < 0)
		aux[i] = '-';
	return (aux);
}
