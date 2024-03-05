/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//vertical collision, take x y vertical and vertical distance.
// determine if the ray direction is right or left to see what texture to put
void	set_ray_property_vert(t_ray_data *ray, double dist, int left)
{
	int	casilla;

	ray->wall_hit_x = ray->wall_hit_x_vert;
	ray->wall_hit_y = ray->wall_hit_y_vert;
	ray->distance = dist;
	casilla = (int)(ray->wall_hit_y / TILE);
	ray->pixel_texturex = ray->wall_hit_y - (casilla * TILE);
	if (left)
		ray->direction = 1;
	else
		ray->direction = 0;
}

//dist distance
//horizontal collision, take x and horiz and horizontal distance.
// determine if the ray direction is up or down to see what texture to put
void	set_ray_property_horiz(t_ray_data *ray, double dist, int down)
{
	int	casilla;

	ray->wall_hit_x = ray->wall_hit_x_horiz;
	ray->wall_hit_y = ray->wall_hit_y_horiz;
	ray->distance = dist;
	casilla = (int)(ray->wall_hit_x / TILE);
	ray->pixel_texturex = ray->wall_hit_x - (casilla * TILE);
	if (down)
		ray->direction = 3;
	else
		ray->direction = 2;
}

//n is the ray number
//We find out the direction in which the ray moves
//Knows if it is down or left depending on the angle
//See if the horizontal or vertical distance is less, to determine
// if there is h or v shock
void	cast(t_ray_data *ray, t_scene_data *sd)
{
	int		down;
	int		left;
	double	horiz_dist;
	double	vert_dist;

	left = 0;
	down = 0;
	if (ray->ray_angle < M_PI)
		down = 1;
	if (ray->ray_angle > M_PI / 2 && ray->ray_angle < 3 * M_PI / 2)
		left = 1;
	horiz_dist = DBL_MAX;
	vert_dist = DBL_MAX;
	if (horizontal_colision(down, left, ray, sd))
		horiz_dist = distance_between_points(ray->x, ray->y,
				ray->wall_hit_x_horiz, ray->wall_hit_y_horiz);
	if (vertical_colision(down, left, ray, sd))
		vert_dist = distance_between_points(ray->x, ray->y,
				ray->wall_hit_x_vert, ray->wall_hit_y_vert);
	if (horiz_dist < vert_dist)
		set_ray_property_horiz(ray, horiz_dist, down);
	else
		set_ray_property_vert(ray, vert_dist, left);
}
