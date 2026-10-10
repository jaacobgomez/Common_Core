/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 22:15:21 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/09 20:27:00 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	manejar_conversion(char c, va_list *args)
{
	if (c == 'c')
		return (ft_print_char(va_arg(*args, int)));
	else if (c == 's')
		return (ft_print_string(va_arg(*args, char *)));
	else if (c == '%')
		return (ft_print_char('%'));
	else if (c == 'i' || c == 'd')
		return (ft_print_int(va_arg(*args, int)));
	else if (c == 'u')
		return (ft_print_uint(va_arg(*args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_print_hexp(va_arg(*args, unsigned int), c));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(*args, void *)));
	else
		return (0);
}

int	ft_printf(char const *fmt, ...)
{
	va_list	args;
	int		i;
	int		contador;

	va_start(args, fmt);
	i = 0;
	contador = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && fmt[i + 1] != '\0')
		{
			i++;
			contador += manejar_conversion(fmt[i], &args);
		}
		else
			contador += write(1, &fmt[i], 1);
		i++;
	}
	va_end(args);
	return (contador);
}
