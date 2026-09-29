/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:00:49 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/03 14:11:18 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	res;
	int	i;

	res = 1;
	i = 2;
	if (nb < 0 || nb > 12)
		return (0);
	while (i <= nb)
	{
		res *= i;
		i++;
	}
	return (res);
}
