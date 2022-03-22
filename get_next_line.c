/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:28:28 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/27 17:51:05 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

static char	*ft_line(char *string)
{
	int		i;
	int		j;
	char	*return_char;

	i = 0;
	j = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	return_char = (char *)malloc(sizeof(char) * (i + 1));
	if (return_char == NULL)
		return (ft_free(string));
	while ((string[j] != '\0' && string[j] != '\n'))
	{
		return_char[j] = string[j];
		j++;
	}
	return_char[i] = '\0';
	return (return_char);
}

static char	*ft_saving(char *string)
{
	int		j;
	int		i;
	char	*return_char;

	j = 0;
	i = 0;
	if (string[i] == '\0')
		return (ft_free(string));
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (string[i] == '\0')
		return (ft_free(string));
	return_char = (char *)malloc(sizeof(char) * (ft_strlen(string) - i + 1));
	if (return_char == NULL)
		return (ft_free(string));
	i = i + 1;
	while (string[i] != '\0')
		return_char[j++] = string[i++];
	return_char[j] = '\0';
	free(string);
	return (return_char);
}

static int	ft_reading_more(int *rc, int fd, char **buffer, char **saved)
{
	char	*temp;

	*rc = read(fd, *buffer, BUFFER_SIZE);
	if (*rc == -1)
	{
		free(*buffer);
		return (-1);
	}
	buffer[0][*rc] = '\0';
	temp = ft_strjoin(*saved, *buffer);
	if (temp == NULL)
	{
		free(*buffer);
		free(*saved);
	}
	free(*saved);
	*saved = temp;
	return (1);
}

static int	ft_saved_initialization(char **saved, char **buffer)
{
	if (*saved == NULL)
	{
		*saved = (char *)malloc(sizeof(char));
		if (*saved == NULL)
		{
			free(*buffer);
			return (-1);
		}
		*saved[0] = '\0';
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			rc;
	static char	*saved;
	char		*buffer;

	rc = 1;
	if (ft_check(line, fd, &saved) == -1 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (-1);
	if (ft_saved_initialization(&saved, &buffer) == -1)
		return (-1);
	while (ft_search(saved) == 0 && rc != 0)
	{
		if (ft_reading_more (&rc, fd, &buffer, &saved) == -1)
			return (-1);
	}
	free(buffer);
	*line = ft_line(saved);
	saved = ft_saving(saved);
	if (rc == 0)
		return (0);
	return (1);
}
