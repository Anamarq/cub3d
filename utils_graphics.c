/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(mlx_t *mlx)
{
	mlx_close_window(mlx);
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	degrees_to_radians(double angle)
{
	angle = angle * (M_PI / 180);
	return (angle);
}

//how to do angle = angle % (2 * PI);
// If the angle is negative, a complete turn is added
double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
