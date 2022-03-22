/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:09:12 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 12:56:35 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function is called in printing, it displays instructions in the left
bottom corner of the screen. y is used to set the space between each line.
*/
void	display_menu(t_window window)
{
	int	y;
	int	color;

	y = W_HEI - 27;
	color = 0xafeeee;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Exit : Esc");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Iso : i");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Parallel : p");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Rotation X : x");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Rotation Y : y");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Rotation Z : z");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Move : arrows");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Increase height : h");
	y -= 17;
	mlx_string_put(window.mlx, window.win, 10, y, color, "Decrease height : b");
}
