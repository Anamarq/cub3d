/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map2d2(t_scene_data *sd, mlx_image_t *tile)
{
	int	x2;
	int	y2;

	x2 = 0;
	y2 = 0;
	while (y2 < sd->altom)
	{
		while (x2 < sd->anchom)
		{
			if (sd->map[y2][x2] == '1')
				if (mlx_image_to_window(sd->mlx, tile, x2 * 10, y2 * 10) < 0)
					error(sd->mlx);
			++x2;
		}
		x2 = 0;
		++y2;
	}
}

//minimapa
void	draw_map2d(t_scene_data *sd)
{
	mlx_image_t	*tile;
	uint32_t	x;
	uint32_t	y;

	tile = mlx_new_image(sd->mlx, 10, 10);
	if (!(tile))
		error(sd->mlx);
	x = 0;
	y = 0;
	while (x < tile->width)
	{
		while (y < tile->height)
		{
			mlx_put_pixel(tile, x, y, ft_pixel(255, 0, 0, 0xFF));
			++y;
		}
		y = 0;
		++x;
	}
	draw_map2d2(sd, tile);
}

//dibuja el personaje 2D en el minimapa
void	draw_character2d(t_scene_data *sd)
{
	uint32_t	x;
	uint32_t	y;

	sd->character = mlx_new_image(sd->mlx, 7, 7);
	if (!(sd->character))
		error(sd->mlx);
	x = 0;
	y = 0;
	while (x < sd->character->width)
	{
		while (y < sd->character->height)
		{
			mlx_put_pixel(sd->character, x, y, ft_pixel(255, 255, 255, 255));
			++y;
		}
		y = 0;
		++x;
	}
	if (mlx_image_to_window(sd->mlx, sd->character,
			sd->ply->x, sd->ply->y) == -1)
		error(sd->mlx);
}

//dibuja el punto de colision de cada rayo
void	draw_end(t_scene_data *scene_data)
{
	uint32_t	x;
	uint32_t	y;

	scene_data->end = mlx_new_image(scene_data->mlx, 1, 1);
	if (!(scene_data->end))
		error(scene_data->mlx);
	x = 0;
	y = 0;
	while (x < scene_data->end->width)
	{
		while (y < scene_data->end->height)
		{
			mlx_put_pixel(scene_data->end, x, y, ft_pixel(255, 255, 255, 255));
			++y;
		}
		y = 0;
		++x;
	}
	while (y < WIDTH)
	{
		if (mlx_image_to_window(scene_data->mlx, scene_data->end, 0, 0) == -1)
			error(scene_data->mlx);
		++y;
	}
}
