/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:41:58 by jacgomez          #+#    #+#             */
/*   Updated: 2026/10/10 22:43:51 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
//calcula la longitud según la tabla y devuelve ft_substr(stash, 0, longitud)
}

static char *cut_stash(char *stash)
{
/*
si no hay \n en la stash, la libera y devuelve NULL. Si lo hay, hace una copia
de lo que queda detrás, libera la vieja y devuelve la copia
(o NULL si el resto está vacío).
*/
}
