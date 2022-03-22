/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_height.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 14:18:19 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 13:55:08 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** These two functions are called by keys_init in keys.c. Len_def (cut in 
two pieces) determines an int that will be used in printing according to
the size of the map. The bigger the map, the smaller len.
*/
int	len_def_bis(t_window window, int side)
{
	if (side > 30 && side <= 40)
		window.len = 20;
	if (side > 40 && side <= 60)
		window.len = 13;
	if (side > 60 && side <= 80)
		window.len = 10;
	if (side > 80 && side <= 110)
		window.len = 7;
	if (side > 110 && side <= 160)
		window.len = 5;
	if (side > 160 && side <= 250)
		window.len = 3;
	if (side > 250 && side <= 320)
		window.len = 2;
	else if (side > 320)
		window.len = 1;
	return (window.len);
}

int	len_def(t_window window)
{
	int	side;

	side = window.height;
	if (window.length > window.height)
		side = window.length;
	if (side <= 5)
		window.len = 100;
	if (side > 5 && side <= 10)
		window.len = 75;
	if (side > 10 && side <= 15)
		window.len = 50;
	if (side > 15 && side <= 20)
		window.len = 35;
	if (side > 20 && side <= 25)
		window.len = 30;
	if (side > 25 && side <= 30)
		window.len = 26;
	if (side > 30)
		window.len = len_def_bis(window, side);
	return (window.len);
}

/*
** This function is called by the next one. The biggest max, the more
divisions need to be made.
*/
int	height_div_categories(int max)
{
	int	height_div;

	if (max < 5)
		height_div = 2;
	if (max >= 5)
		height_div = 4;
	if (max >= 10)
		height_div = 6;
	if (max >= 30)
		height_div = 8;
	if (max >= 60)
		height_div = 16;
	return (height_div);
}

/*
** This function looks for the biggest number in the map to find a int that
will be used to calculate the length of the relief segments to be sure they fit
in the map.
*/
int	height_div(t_window window, int **array)
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
	return (height_div_categories(max));
}
