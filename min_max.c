/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:09:18 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 13:32:39 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** These two functions will be used in color_init to determinate the start and 
end color of each segment according to the maximum and minimum z. It iterates 
in the array to find the maximum value.
*/
int	get_max(t_window window, int **array)
{
	int	max;
	int	x;
	int	y;

	max = array[0][0];
	y = 0;
	while (y < window.length)
	{
		x = 0;
		while (x < window.height)
		{
			if (array[x][y] > max)
				max = array[x][y];
			x++;
		}
		y++;
	}
	return (max);
}

/*
** It iterates in the array to find the minimum value.
*/
int	get_min(t_window window, int **array)
{
	int	min;
	int	x;
	int	y;

	min = array[0][0];
	y = 0;
	while (y < window.length)
	{
		x = 0;
		while (x < window.height)
		{
			if (array[x][y] < min)
				min = array[x][y];
			x++;
		}
		y++;
	}
	return (min);
}
