/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

//XIntercept is the following x horiz
//Loop to search for collision point. As long as there is no crash
//tile_x, and We obtain the square by rounding down
//If there is a collision, wallHitX is assigned.
// If not, we advance to the next box
int	loop_colision_horiz(t_colision_data col_data, t_ray_data *ray,
		t_scene_data *sd)
{
	int	next_x;
	int	next_y;
	int	tile_x;
	int	tile_y;

	next_x = col_data.x_intercept;
	next_y = col_data.y_intercept;
	while ((next_x >= 0 && next_y >= 0
			&& next_x < sd->anchom * TILE && next_y < sd->altom * TILE))
	{
		tile_x = (int)(next_x / TILE);
		tile_y = (int)(next_y / TILE);
		if (scene_colision(sd, tile_x, tile_y))
		{
			ray->wall_hit_x_horiz = next_x;
			ray->wall_hit_y_horiz = next_y;
			return (1);
		}
		else
		{
			next_x += col_data.x_step;
			next_y += col_data.y_step;
		}
	}
	return (0);
}

//y_intercept Find first intersection. y2
//If it points down we increment a tile
//The y of the triangle that is formed dif between y2 - y1.
//xady=(y2-y1)/tan(angle)
//adjacent = (yIntercept - sd->ray->y) / tan(sd->ray->ray_angle);
//y step, s xtep: We calculate the distance of each step, tile
//If we go up, reverse step Y
//We check that step x is coherent
//If it goes to the left it cannot be greater than 0
//If it points up, I subtract one pixel to force the collision with
//the box, if not, there is a false collision
int	horizontal_colision(int down, int left, t_ray_data *ray, t_scene_data *sd)
{
	t_colision_data	col_data;

	col_data.x_intercept = 0;
	col_data.y_intercept = 0;
	col_data.x_step = 0;
	col_data.y_step = 0;
	col_data.y_intercept = floor(ray->y / TILE) * TILE;
	if (down)
		col_data.y_intercept += TILE;
	col_data.x_intercept = (col_data.y_intercept - ray->y)
		/ tan(ray->ray_angle) + ray->x;
	col_data.y_step = TILE;
	col_data.x_step = col_data.y_step / tan(ray->ray_angle);
	if (!down)
		col_data.y_step = -col_data.y_step;
	if ((left && col_data.x_step > 0) || (!left && col_data.x_step < 0))
		col_data.x_step = -col_data.x_step;
	if (!down)
		--col_data.y_intercept;
	return (loop_colision_horiz(col_data, ray, sd));
}

//XIntercept is the following x vert
//Loop to search for collision point. As long as there is no crash
//tile_x, and We obtain the square by rounding down
//If there is a collision, wallHitX is assigned. If not, we advance to the next box
int	loop_colision_vert(t_colision_data col_data, t_ray_data *ray,
	t_scene_data *sd)
{
	int	next_x;
	int	next_y;
	int	tile_x;
	int	tile_y;

	next_x = col_data.x_intercept;
	next_y = col_data.y_intercept;
	while ((next_x >= 0 && next_y >= 0 && next_x < sd->anchom * TILE
			&& next_y < sd->altom * TILE))
	{
		tile_x = (int)(next_x / TILE);
		tile_y = (int)(next_y / TILE);
		if (scene_colision(sd, tile_x, tile_y))
		{
			ray->wall_hit_x_vert = next_x;
			ray->wall_hit_y_vert = next_y;
			return (1);
		}
		else
		{
			next_x += col_data.x_step;
			next_y += col_data.y_step;
		}
	}
	return (0);
}

//x_intercept Find first intersection. x2
//If it points to the right we increment a tile
//add the opposite leg
//double opposite=(col_data.x_intercept - sd->ray->x) * tan(sd->ray->ray_angle)
//y step, s xtep: We calculate the distance of each step, tile
//If we go left, reverse step x
//We check that step y is coherent
//If it goes to the top it cannot be greater than 0
//If it points to the left, I subtract one pixel to force
//the collision with the box, if not, there is a false collision
int	vertical_colision(int down, int left, t_ray_data *ray, t_scene_data *sd)
{
	t_colision_data	col_data;

	col_data.x_intercept = 0;
	col_data.y_intercept = 0;
	col_data.x_step = 0;
	col_data.y_step = 0;
	col_data.x_intercept = floor(ray->x / TILE) * TILE;
	if (!left)
		col_data.x_intercept += TILE;
	col_data.y_intercept = (col_data.x_intercept - ray->x)
		* tan(ray->ray_angle) + ray->y;
	col_data.x_step = TILE;
	col_data.y_step = col_data.x_step * tan(ray->ray_angle);
	if (left)
		col_data.x_step = -col_data.x_step;
	if ((!down && col_data.y_step > 0) || (down && col_data.y_step < 0))
		col_data.y_step = -col_data.y_step;
	if (left)
		col_data.x_intercept--;
	return (loop_colision_vert(col_data, ray, sd));
}
