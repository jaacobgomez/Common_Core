/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacgomez <jacgomez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 22:32:30 by jacgomez          #+#    #+#             */
/*   Updated: 2026/09/23 23:11:30 by jacgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	ft_display(int fd)
{
	char	buf[4096];
	int		res;

	res = read(fd, buf, 4096);
	while (res > 0)
	{
		write(1, buf, res);
		res = read(fd, buf, 4096);
	}
	return (res);
}

int	argc_errors(int argc)
{
	if (argc == 1)
	{
		write(2, "File name missing.\n", 19);
		return (1);
	}
	else if (argc > 2)
	{
		write(2, "Too many arguments.\n", 20);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc_errors(argc))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 || ft_display(fd) == -1)
	{
		write(2, "Cannot read file.\n", 18);
		if (fd != -1)
			close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
