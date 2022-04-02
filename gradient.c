/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:02:28 by mdeclerf          #+#    #+#             */
/*   Updated: 2022/04/02 15:49:44 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function initializes the structure t_color that contains an int for R,
for G and for B. It is used in the loops of printing to init the t_colors of 
the start and end points of each segment.
*/
t_color	colorstruct_init(t_color co)
{
	co.R = 0;
	co.G = 0;
	co.B = 0;
	return (co);
}

/*
** This function creates an int out of three chars, R, G and B (A for light).
It uses a char[4] where each index is a color, that will be casted as an int.
*/
int	create_argb(char a, char r, char g, char b)
{
	char	argb_c[4];
	int		*argb_i;

	argb_c[3] = a;
	argb_c[2] = r;
	argb_c[1] = g;
	argb_c[0] = b;
	argb_i = (int *)argb_c;
	return (*argb_i);
}

/*
** This function is used in the two gradient functions. It returns a value 
between 0 and 1 which is the position of the current point between 
the start and end point.  The first exit condition makes sure no 
division by 0 is made.
*/
double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (placement / distance);
}

/*
** This function is used to assign a color to start and end t_points in printing.
It calculates this color taking the minimum and maximum heights as start and end 
colors. The current height is the int current_z. t_color storage is a temp struct
that will replace the grad.A or grad.B in printing.
*/
t_color	color_init(int current_z, t_window window, t_color storage)
{
	t_color	a;
	t_color	b;
	float	min;
	float	max;
	float	copy;

	a.R = 255;
	a.G = 192;
	a.B = 203;
	b.R = 152;
	b.G = 251;
	b.B = 152;

	// a.R = 255;
	// a.G = 99;
	// a.B = 71;
	// b.R = 123;
	// b.G = 104;
	// b.B = 238;
	
	min = (float)(get_min(window, window.array));
	max = (float)(get_max(window, window.array));
	copy = percent(min, max, current_z);
	storage.R = a.R - copy * (a.R - b.R);
	storage.G = a.G - copy * (a.G - b.G);
	storage.B = a.B - copy * (a.B - b.B);
	return (storage);
}

/*
** This function is used to create a gradient within each segment, using the 
colors calculated above for end and start. It is called in segment, so that 
every pixel will have a different color. The delta value is used to check 
if amplitude of the vector is greater on the x or y axis.
*/
int	color_handling(t_point end, t_point start, t_bresen bresen, t_grad grad)
{
	double	percentage;
	t_color	currentcolor;

	if (bresen.delta.x > bresen.delta.y)
		percentage = percent(start.x, end.x, bresen.current.x);
	else
		percentage = percent(start.y, end.y, bresen.current.y);
	currentcolor.R = grad.A.R - percentage * (grad.A.R - grad.B.R);
	currentcolor.G = grad.A.G - percentage * (grad.A.G - grad.B.G);
	currentcolor.B = grad.A.B - percentage * (grad.A.B - grad.B.B);
	return (create_argb('\0', currentcolor.R,
			currentcolor.G, currentcolor.B));
}
