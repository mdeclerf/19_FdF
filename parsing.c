/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:09:24 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 12:09:26 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function returns the number of lines in the map.
*/
int	get_height(char **argv)
{
	int		ret;
	int		i;
	int		fd;
	char	**line;

	line = malloc(sizeof(char *));
	fd = open(argv[1], O_RDONLY);
	i = 0;
	ret = 2;
	while (ret > 0)
	{
		ret = get_next_line(fd, line);
		if (ft_strlen(*line) > 1)
			i++;
		free(*line);
	}
	free(line);
	close (fd);
	return (i);
}

/*
** This function returns the number of elements in a line of the map.
*/
int	get_length(char **argv)
{
	int		fd;
	int		i;
	char	**line;

	fd = open(argv[1], O_RDONLY);
	line = malloc(sizeof(char *));
	get_next_line(fd, line);
	i = string_number(*line, ' ');
	free(*line);
	free(line);
	close(fd);
	return (i);
}

/*
** This function creates a 2d array, where each line will have
enough space for each point of th line.
*/
int	**allocate_array(t_window window)
{
	int	i;
	int	j;
	int	**array;

	i = 0;
	j = 0;
	array = (int **) malloc(sizeof(int *) * window.height);
	while (i < window.height)
	{
		j = 0;
		array[i] = (int *) malloc(sizeof(int) * window.length);
		i++;
	}
	return (array);
}

/*
** This function uses get_next_line to read each line and split to cut them,
using ' ' as a delimitor.
*/
char	**loop_fill_array(int fd, char **backup)
{
	char	**line;

	line = malloc(sizeof(char *));
	get_next_line(fd, line);
	backup = ft_split(*line, ' ');
	free(*line);
	free(line);
	return (backup);
}

/*
** This function fills the previously allocated array with the content of the map
WARNING : the parsing is reversed, x and y are switched later on in the code.
*/
int	**fill_array(t_window window, int **array, char **argv)
{
	int		i;
	int		j;
	int		fd;
	char	**backup;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (i < window.height)
	{
		backup = loop_fill_array(fd, backup);
		j = 0;
		while (j < window.length)
		{
			array[i][j] = ft_atoi(backup[j]);
			free(backup[j]);
			j++;
		}
		free(backup);
		i++;
	}
	close(fd);
	return (array);
}
