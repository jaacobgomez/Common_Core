/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_csuid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 15:46:20 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/09 18:14:47 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	return (write(1, &ch, 1));
}

int	ft_print_string(char *s)
{
	size_t	len;

	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}

int	ft_print_uint(unsigned long n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len = ft_print_uint(n / 10);
	len += ft_print_char('0' + n % 10);
	return (len);
}

int	ft_print_int(int c)
{
	int		len;
	int		len_u;
	long	n;

	n = (long)c;
	len = 0;
	if (n < 0)
	{
		len = ft_print_char('-');
		n = -n;
	}
	len_u = ft_print_uint(n);
	return (len + len_u);
}
