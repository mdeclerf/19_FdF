/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:09:38 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 12:09:41 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** Initialization of the t_point structures to be used in printing
*/
t_point	point_init(t_point point)
{
	point.x = 0;
	point.y = 0;
	point.z = 0;
	return (point);
}

/*
** First the grad struct (used for the handling of the colors) is initialized.
The x and y of start are defined based on variables in window (modified with to 
events or according to the size of the map). Color_init gives color to end and 
start according to the min and max altitude. Start and End are modified if 
a rotation is asked.
*/
void	loop_1(t_window window, t_coord coord, int x, int y)
{
	t_grad	grad;

	grad.A = colorstruct_init(grad.A);
	grad.B = colorstruct_init(grad.B);
	coord.start.x = x * window.len + window.start_x;
	coord.start.y = y * window.len + window.start_y;
	coord.start.z = window.array[y][x] * window.ampli;
	grad.A = color_init(window.array[y][x], window, grad.A);
	coord.start = rotation_iso(coord.start, window);
	coord.end.x = (x + 1) * window.len + window.start_x;
	coord.end.y = y * window.len + window.start_y;
	coord.end.z = window.array[y][x + 1] * window.ampli;
	grad.B = color_init(window.array[y][x + 1], window, grad.B);
	coord.end = rotation_iso(coord.end, window);
	segment(&window, coord.start, coord.end, grad);
}

/*
** Same as before, instead of incrementing x for the end point, we increment y
*/
void	loop_2(t_window window, t_coord coord, int x, int y)
{
	t_grad	grad;

	grad.A = colorstruct_init(grad.A);
	grad.B = colorstruct_init(grad.B);
	coord.start.x = x * window.len + window.start_x;
	coord.start.y = y * window.len + window.start_y;
	coord.start.z = window.array[y][x] * window.ampli;
	grad.A = color_init(window.array[y][x], window, grad.A);
	coord.start = rotation_iso(coord.start, window);
	coord.end.x = x * window.len + window.start_x;
	coord.end.y = (y + 1) * window.len + window.start_y;
	coord.end.z = window.array[y + 1][x] * window.ampli;
	grad.B = color_init(window.array[y + 1][x], window, grad.B);
	coord.end = rotation_iso(coord.end, window);
	segment(&window, coord.start, coord.end, grad);
}

/*
** This function prints the different segments composing the drawing.
The t_points start and end are stored in a struct : coord. Once the segments have
been traced on the image, it is displayed to the window and the menu displayed.
*/
void	printing(t_window window)
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
			if (x != window.length - 1)
				loop_1(window, coord, x, y);
			if (y != window.height - 1)
				loop_2(window, coord, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
	display_menu(window);
}
