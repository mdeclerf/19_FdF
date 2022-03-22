/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:02:05 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 12:02:07 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function checks if there is only one map
given as argument and if it exists
*/
int	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		write(1, "Invalid number of arguments\n", 28);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "Does this map exist ?\n", 22);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*
** This function checks that each line of the map has the same
number of points. It uses a get_next_line to compare the number of
points of every number with one calculated before in the main 
(get_length(int argv))
*/
int	check_map(char **argv, t_window window)
{
	char	**line;
	int		fd;

	line = malloc(sizeof(char *));
	fd = open(argv[1], O_RDONLY);
	while (window.height > 0)
	{
		get_next_line(fd, line);
		if (string_number(*line, ' ') != window.length)
		{
			free(*line);
			free(line);
			return (-1);
		}
		window.height--;
		free(*line);
	}
	free(line);
	close(fd);
	return (0);
}
