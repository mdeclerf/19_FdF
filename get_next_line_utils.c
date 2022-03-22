/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:28:17 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 13:02:26 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*cat;

	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	cat = (char *)malloc(sizeof(char) * (len + 1));
	if (cat == NULL)
		return (NULL);
	while (*s1 != '\0')
		cat[i++] = *s1++;
	while (*s2 != '\0')
		cat[i++] = *s2++;
	cat[i] = '\0';
	return (cat);
}

int	ft_search(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_free(char *string)
{
	free(string);
	return (NULL);
}

int	ft_check(char **line, int fd, char **saved)
{
	if (line == NULL || fd < 0)
	{
		if (*saved != NULL)
			free(*saved);
		return (-1);
	}
	else
		return (1);
}
