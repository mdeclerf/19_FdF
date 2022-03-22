/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:02:43 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 13:34:38 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function is taken as a parameter by "mlx_hook(window.win, 17, 1L << 17,
close_x, &window)" in the main. It has to have a void * as a parameter, that is 
not used here. The 17 stands for "Destroy notify" and the 1L << 17 for 
"StructureNotifyMask". It makes the cross exit happen.
*/
int	close_x(void *param)
{
	(void)param;
	exit(0);
}

/*
** This function initializes variables stored in window that will be influenced
by events. The len will be used to determine the size of each segment, ampli to
determine the height of the relief, parallel and iso to launch or not the iso 
function.
*/
t_window	keys_init(t_window window, int **array)
{
	window.len = len_def(window);
	window.height_div = height_div(window, array);
	window.ampli = window.len / window.height_div;
	window.parallel = 0;
	window.start_x = 0;
	window.start_y = 0;
	window.iso = 1;
	window.array = array;
	window.rot_x = 0;
	window.rot_y = 0;
	window.rot_z = 0;
	return (window);
}

int	keys_move_bis(int key, t_window *window)
{
	if (key == KEY_PAR)
	{
		window->iso = 0;
		window->parallel = 1;
	}
	else if (key == KEY_H_PLUS)
		window->ampli += 1;
	else if (key == KEY_H_MIN)
		window->ampli -= 1;
	else if (key == KEY_X)
		window->rot_x += 2;
	else if (key == KEY_Y)
		window->rot_y += 2;
	else if (key == KEY_Z)
		window->rot_z += 2;
	return (0);
}

/*
** This function is taken as a parameter by "mlx_hook(window.win, 2, 0, 
keys_move, &window);" The first thing to do in this function is to cover the
previous drawing (printblack), then increment or decrememt variables in window 
according to the key pressed, variables that will later on be used in the 
printing functions. Once window have been modified, a new print is done.
*/
int	keys_move(int key, t_window *window)
{
	printblack(*window);
	if (key == KEY_ESC)
	{
		mlx_destroy_window(window->mlx, window->win);
		exit(0);
	}
	else if (key == KEY_UP)
		window->start_y -= 4;
	else if (key == KEY_DOWN)
		window->start_y += 4;
	else if (key == KEY_LEFT)
		window->start_x -= 4;
	else if (key == KEY_RIGHT)
		window->start_x += 4;
	else if (key == KEY_ISO)
	{
		window->iso = 1;
		window->parallel = 0;
	}
	else if (key == KEY_PAR || key == KEY_H_PLUS
		|| key == KEY_H_MIN || key == KEY_X
		|| key == KEY_Y || key == KEY_Z)
		keys_move_bis(key, window);
	printing(*window);
	return (0);
}
