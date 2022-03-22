/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeclerf <mdeclerf@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:09:04 by mdeclerf          #+#    #+#             */
/*   Updated: 2021/07/28 13:49:44 by mdeclerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

/*
** Rotation matrice by x : changes the coordinates of the t_point according
to an angle. This function is called by rotation_iso, called by printing. The
int backup allows to modify save point.y to be able to calculate point.z even if
point.y has been modified.
*/
t_point	rotation_x(t_point point, double angle)
{
	int	backup;

	backup = point.y;
	point.y = 0 * point.x + cos(angle) * point.y + -sin(angle) * point.z;
	point.z = 0 * point.x + sin(angle) * backup + cos(angle) * point.z;
	return (point);
}

/*
** Rotation matrice by y.
*/
t_point	rotation_y(t_point point, double angle)
{
	int	backup;

	backup = point.x;
	point.x = cos(angle) * point.x + 0 * point.y + sin(angle) * point.z;
	point.z = -sin(angle) * backup + 0 * point.y + cos(angle) * point.z;
	return (point);
}

/*
** Rotation matrice by z.
*/
t_point	rotation_z(t_point point, double angle)
{
	int	backup;

	backup = point.x;
	point.x = cos(angle) * point.x + -sin(angle) * point.y + 0 * point.z;
	point.y = sin(angle) * backup + cos(angle) * point.y + 0 * point.z;
	return (point);
}

/*
** This function will change the coordinates of a point if the bool for 
iso is set to 1. An isometric projection uses a 30 degree angle, this
function performs a rotation in the coordinates of point to fit the iso
projection.
*/
t_point	iso(t_point point)
{
	int	backup;

	backup = point.x;
	point.x = (point.x - point.y) * cos(0.523599);
	point.y = -point.z + (backup + point.y) * sin(0.523599);
	return (point);
}

/*
** This function performs three tasks : changing point according
to the rotations. The angle is given in radian : the variable changed 
by events is multiplied by pi and divided by 180 degrees / it sends point 
to be modified by iso if needed / it centers the drawing according to the 
size of the screen. 
*/
t_point	rotation_iso(t_point point, t_window window)
{
	point = rotation_x(point, window.rot_x * M_PI / (double)180);
	point = rotation_y(point, window.rot_y * M_PI / (double)180);
	point = rotation_z(point, window.rot_z * M_PI / (double)180);
	if (window.iso == 1)
	{
		point = iso(point);
		point.x += W_WID / 2;
		point.y += (W_HEI - (window.height * window.len)) / 2;
	}
	else if (window.iso == 0)
	{
		point.x += (W_WID - (window.length * window.len)) / 2;
		point.y += (W_HEI - (window.height * window.len)) / 2;
	}
	return (point);
}
