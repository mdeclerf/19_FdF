/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:09:30 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 14:22:20 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function is a custom put_pixel function. If the pixel is out of the 
size of the window or has a negative value, it returns. Ll stands for the 
length of the line and b_p_p bit per pixel. We calculate the memory offset
between the image to put in the window and the pixels to draw.
*/
void	my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= W_WID || y >= W_HEI)
		return ;
	dst = window->addr + (y * window->ll + x * (window->b_p_p / 8));
	*(unsigned int *)dst = color;
}

/*
** Helper function of the two below : all the elements necessary to draw
the segment are stored in a struct.
*/
t_bresen	segment_preparation(t_point startpoint, t_point endpoint)
{
	t_bresen	bresen;

	bresen.delta.x = abs(endpoint.x - startpoint.x);
	bresen.delta.y = abs(endpoint.y - startpoint.y);
	if (startpoint.x < endpoint.x)
		bresen.sign.x = 1;
	else
		bresen.sign.x = -1;
	if (startpoint.y < endpoint.y)
		bresen.sign.y = 1;
	else
		bresen.sign.y = -1;
	if (bresen.delta.x > bresen.delta.y)
		bresen.err = bresen.delta.x / 2;
	else
		bresen.err = -bresen.delta.y / 2;
	bresen.current = startpoint;
	return (bresen);
}

/*
** This function is the algorithm of Bresenham. It has a loop that 
draws a pixel until the current point is at the level of the end point.
This function is used by printing and calls the inner segment gradient
function.
*/
void	segment(t_window *window, t_point startpoint,
				t_point endpoint, t_grad grad)
{
	t_bresen	bresen;

	bresen = segment_preparation(startpoint, endpoint);
	while (bresen.current.x != endpoint.x || bresen.current.y != endpoint.y)
	{
		my_mlx_pixel_put(window, bresen.current.x, bresen.current.y,
			color_handling(endpoint, startpoint, bresen, grad));
		bresen.e2 = bresen.err;
		if (bresen.e2 > -bresen.delta.x)
		{
			bresen.err -= bresen.delta.y;
			bresen.current.x += bresen.sign.x;
		}
		if (bresen.e2 < bresen.delta.y)
		{
			bresen.err += bresen.delta.x;
			bresen.current.y += bresen.sign.y;
		}
	}
}

/*
** Same as before. Except that this function is used by printing_mute
and prints in black.
*/
void	segment_mute(t_window *window, t_point startpoint,
					 t_point endpoint, int color)
{
	t_bresen	bresen;

	bresen = segment_preparation(startpoint, endpoint);
	while (bresen.current.x != endpoint.x || bresen.current.y != endpoint.y)
	{
		my_mlx_pixel_put(window, bresen.current.x, bresen.current.y, color);
		bresen.e2 = bresen.err;
		if (bresen.e2 > -bresen.delta.x)
		{
			bresen.err -= bresen.delta.y;
			bresen.current.x += bresen.sign.x;
		}
		if (bresen.e2 < bresen.delta.y)
		{
			bresen.err += bresen.delta.x;
			bresen.current.y += bresen.sign.y;
		}
	}
}
