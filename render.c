/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculate the index of the pixel in the pixel buffer
// Multiplied by 4 to take into account the 4 bytes per pixel (RGBA)
//Access the pixel buffer and combine the RGBA values ​​into a single uint32_t
uint32_t	get_pixel_color(int x, int y, mlx_image_t *tx)
{
	int			index;
	uint32_t	color;

	index = (y * tx->width + x) * 4;
	color = (tx->pixels[index] << 24) | (tx->pixels[index + 1] << 16)
		| (tx->pixels[index + 2] << 8) | tx->pixels[index + 3];
	return (color);
}

//choose the texture according to the direction
mlx_image_t	*choose_tx(t_scene_data *sd, int n)
{
	if (n == 0)
		return (sd->walls.tx_right);
	else if (n == 1)
		return (sd->walls.tx_left);
	else if (n == 2)
		return (sd->walls.tx_up);
	else if (n == 3)
		return (sd->walls.tx_down);
	return (NULL);
}

//y0, y1 We calculate where the line begins and ends
//y0 half screen - half wall
//y1 where it ends
//the y0aux, y1aux is for the actual line, which goes off the screen.
//y0,y1 is the line that is drawn,which is limited so that it doesnt segfault
//in the loop a rule of 3 is made to choose the texture pixel and.
//the loop draws the line
void	render_wall(t_scene_data *sd, t_ray_data ray)
{
	t_render_data	rd;
	int				y;
	uint32_t		color;

	rd.plane_distance = (WIDTH / 2) / tan(FOV / 2.0);
	rd.hight_wall = (TILE * 10 / ray.distance) * rd.plane_distance;
	rd.y0 = (int)(HEIGHT / 2) - (int)(rd.hight_wall / 2);
	rd.y1 = rd.y0 + rd.hight_wall;
	rd.x = ray.columna;
	rd.y0aux = rd.y0;
	rd.y1aux = rd.y1;
	if (rd.y0 >= HEIGHT)
		rd.y0 = HEIGHT - 1;
	if (rd.y1 < 0)
		rd.y1 = 0;
	y = rd.y1;
	while (y < rd.y0)
	{
		rd.py = TILE * (y - rd.y1aux) / (rd.y0aux - rd.y1aux);
		color = get_pixel_color(ray.pixel_texturex, rd.py,
				choose_tx(sd, ray.direction));
		mlx_put_pixel(sd->scene, rd.x, y, color);
		++y;
	}
}

// Set the pixel to black
//is necessary to update the image, how to clear the buffer
void	clear_screen(mlx_image_t *scene)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < WIDTH)
	{
		while (i < HEIGHT)
		{
			mlx_put_pixel(scene, x, i, 0x000000);
			++i;
		}
		i = 0;
		++x;
	}
}

//for each ray:
//the current angle is calculated
//after the cast: Fisheye correction
//calculate where the end is drawn on the minimap
void	calculate_ray(t_scene_data *sd)
{
	int	xdest;
	int	ydest;
	int	i;

	clear_screen(sd->scene);
	i = 0;
	while (i < WIDTH)
	{
		sd->ray[i].ray_angle = normalize_angle(sd->ply->rot_angle
				+ sd->ray[i].step_angle);
		sd->ray[i].x = sd->ply->x;
		sd->ray[i].y = sd->ply->y;
		cast(&sd->ray[i], sd);
		sd->ray[i].distance = sd->ray[i].distance * cos(sd->ply->rot_angle
				- sd->ray[i].ray_angle);
		render_wall(sd, sd->ray[i]);
		xdest = sd->ray[i].wall_hit_x;
		ydest = sd->ray[i].wall_hit_y;
		sd->end->instances[i].x = xdest / (TILE / 10);
		sd->end->instances[i].y = ydest / (TILE / 10);
		++i;
	}
}
