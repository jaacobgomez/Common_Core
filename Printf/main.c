/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 18:18:21 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/09 20:37:37 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;

	a = ft_printf("[%d|%i|%u]\n", 0, -42, -1);
	b = printf("[%d|%i|%u]\n", 0, -42, -1);
	printf("%d %d\n", a, b);
	a = ft_printf("[%d|%d|%u]\n", INT_MIN, INT_MAX, UINT_MAX);
	b = printf("[%d|%d|%u]\n", INT_MIN, INT_MAX, UINT_MAX);
	printf("%d %d\n", a, b);
	a = ft_printf("[%x|%x|%x|%X]\n", 0, 255, -1, 255);
	b = printf("[%x|%x|%x|%X]\n", 0, 255, -1, 255);
	printf("%d %d\n", a, b);
	a = ft_printf("[%p|%p|%%]\n", NULL, &a);
	b = printf("[%p|%p|%%]\n", NULL, &a);
	printf("%d %d\n", a, b);
	return (0);
}
