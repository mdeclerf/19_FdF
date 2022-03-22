/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:01:54 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 12:57:21 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** This function is called at the end of the main and is used to free the 
2d array where the points of the map are stored.
*/
void	free_array(t_window window, int **array)
{	
	int	i;

	i = 0;
	while (i < window.height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
