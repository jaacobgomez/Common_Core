/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:26:14 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/10 21:15:20 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexp(unsigned long n, int c)
{
	char	*base;
	int		len;

	if ((char)c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
		len = ft_print_hexp(n / 16, c);
	len += ft_print_char(base[n % 16]);
	return (len);
}

int	ft_print_ptr(void *p)
{
	int	len;

	len = 0;
	if (p == NULL)
		return (ft_print_string("(nil)"));
	len = ft_print_string("0x");
	len += ft_print_hexp((unsigned long)p, 'x');
	return (len);
}
