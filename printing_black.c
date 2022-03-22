/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_black.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:03:01 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 12:05:56 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

void	loop_1_black(t_window window, t_coord coord, int x, int y)
{
	coord.start.x = x * window.len + window.start_x;
	coord.start.y = y * window.len + window.start_y;
	coord.start.z = window.array[y][x] * window.ampli;
	coord.start = rotation_iso(coord.start, window);
	coord.end.x = (x + 1) * window.len + window.start_x;
	coord.end.y = y * window.len + window.start_y;
	coord.end.z = window.array[y][x + 1] * window.ampli;
	coord.end = rotation_iso(coord.end, window);
	segment_mute(&window, coord.start, coord.end, 0x0);
}

void	loop_2_black(t_window window, t_coord coord, int x, int y)
{
	coord.start.x = x * window.len + window.start_x;
	coord.start.y = y * window.len + window.start_y;
	coord.start.z = window.array[y][x] * window.ampli;
	coord.start = rotation_iso(coord.start, window);
	coord.end.x = x * window.len + window.start_x;
	coord.end.y = (y + 1) * window.len + window.start_y;
	coord.end.z = window.array[y + 1][x] * window.ampli;
	coord.end = rotation_iso(coord.end, window);
	segment_mute(&window, coord.start, coord.end, 0x0);
}

/*
** This function will be called in keys_move, function called by mlx_hook. 
Every time an event requires the drawing to change (rotation, height...), the 
previous drawing is traced on the same spot in black and the coordinated 
of end and start are modified and new segments are traced again.
*/
void	printblack(t_window window)
{
	int		x;
	int		y;
	t_coord	coord;

	coord.start = point_init(coord.start);
	coord.end = point_init(coord.end);
	y = 0;
	while (y < window.height)
	{
		x = 0;
		while (x < window.length)
		{
			if (x != window.length - 1 && x >= 0)
				loop_1_black(window, coord, x, y);
			if (y != window.height - 1 && y >= 0)
				loop_2_black(window, coord, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
}
