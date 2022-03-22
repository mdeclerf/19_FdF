/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:07:51 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 14:23:24 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** parsing, init of the mlx / creation of a window and an image
to put in the window : the mlx_get_data_addr function returns 
information about the created image / Initialization of the 
variables stored in window that will be modified by events. /
mlx_get_data_addr : get the adress of the image to put to the
window (done in printing with "mlx_put_image_to_window")
*/
t_window	main_bis(t_window window, int **array)
{
	array = allocate_array(window);
	array = fill_array(window, array, window.argv);
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, W_WID, W_HEI, "window");
	window.img = mlx_new_image(window.mlx, W_WID, W_HEI);
	window.addr = mlx_get_data_addr(window.img, &window.b_p_p,
			&window.ll, &window.e);
	window = keys_init(window, array);
	return (window);
}

/*
** check of the errors, getting the height and length of the map 
(counted in number of elements), mlx_hook for the events (keys and esc),
print of the fdf structure and free of the parsing array.
*/
int	main(int argc, char **argv)
{
	int			**array;
	t_window	window;

	array = NULL;
	window.argv = argv;
	if (check_args(argc, argv) == -1)
		return (-1);
	window.height = get_height(argv);
	window.length = get_length(argv);
	if (check_map(argv, window) == -1)
	{
		write(1, "Invalid map\n", 12);
		return (-1);
	}
	window = main_bis(window, array);
	mlx_hook(window.win, 2, 0, keys_move, &window);
	mlx_hook(window.win, 17, 1L << 17, close_x, &window);
	printing(window);
	mlx_loop(window.mlx);
	free_array(window, window.array);
	free_array(window, array);
	return (0);
}
