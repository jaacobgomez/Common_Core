/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 21:50:56 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/09 20:14:30 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

int	ft_print_string(char *s);
int	ft_print_char(int c);
int	ft_print_uint(unsigned long n);
int	ft_print_int(int c);
int	ft_print_hexp(unsigned long n, int c);
int	ft_print_ptr(void *p);
int	ft_printf(char const *fmt, ...);

#endif
