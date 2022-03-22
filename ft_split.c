/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:02:17 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 13:01:31 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function is used for the split and to check that the map is correct in
error_check.c
*/
int	string_number(char const *s, char c)
{
	int	how_many;
	int	i;

	how_many = 0;
	i = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (i == 0 && *s != c)
		{
			i = 1;
			how_many ++;
		}
		else if (i == 1 && *s == c)
			i = 0;
		s ++;
	}
	return (how_many);
}

int	str_len(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

char	**error_malloc(char **array, int string_count)
{
	while (string_count > 0)
	{
		string_count--;
		free(array[string_count]);
	}
	free(array);
	return (NULL);
}

char	**copy(char const *s, char **array, char c, int string_number)
{
	int	char_c;
	int	string_c;
	int	i;

	char_c = 0;
	string_c = 0;
	while (s[char_c] != '\0' && string_c < string_number)
	{
		i = 0;
		while (s[char_c] == c)
			char_c++;
		array[string_c] = malloc(sizeof(char) * (str_len(s, c, char_c) + 1));
		if (array[string_c] == NULL)
			return (error_malloc(array, string_c));
		while (s[char_c] != c && s[char_c] != '\0')
		{
			array[string_c][i] = s[char_c];
			i++;
			char_c++;
		}
		array[string_c][i] = '\0';
		string_c++;
	}
	return (array);
}

/*
** Allocates and returns an array of strings obtained by splitting 
’s’ using the character ’c’ as a delimiter. The array must be ended
by a NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	char	**array;
	int		how_many_strings;

	if (s == NULL)
		return (NULL);
	how_many_strings = string_number(s, c);
	array = malloc(sizeof(char *) * (how_many_strings + 1));
	if (array == NULL)
		return (NULL);
	array[how_many_strings] = (NULL);
	return (copy(s, array, c, how_many_strings));
}
