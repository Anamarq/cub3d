/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//step_angle Tells how much each ray increases
//with ray_angle I start on the left side
void	initialize_ray(t_scene_data *sd)
{
	double	step_angle;
	double	ray_angle;
	int		i;

	step_angle = degrees_to_radians(60.0 / WIDTH);
	ray_angle = degrees_to_radians(sd->ply->rot_angle - 30);
	i = -1;
	while (++i < WIDTH)
	{
		sd->ray[i].x = sd->ply->x;
		sd->ray[i].y = sd->ply->y;
		sd->ray[i].ray_angle = sd->ply->rot_angle + ray_angle;
		sd->ray[i].step_angle = ray_angle;
		sd->ray[i].distance = 0.0;
		sd->ray[i].pixel_texturex = 0;
		sd->ray[i].direction = -1;
		sd->ray[i].columna = i;
		ray_angle += step_angle;
		sd->ray[i].wall_hit_x = 0;
		sd->ray[i].wall_hit_y = 0;
		sd->ray[i].wall_hit_x_horiz = 0;
		sd->ray[i].wall_hit_y_horiz = 0;
		sd->ray[i].wall_hit_x_vert = 0;
		sd->ray[i].wall_hit_y_vert = 0;
	}
}

void	reserve_memory_map(t_scene_data *scene_data, t_data parse_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	scene_data->map = malloc(parse_data.y * sizeof(char *));
	if (scene_data->map == NULL)
	{
		free(scene_data->map);
		exit(EXIT_FAILURE);
	}
	while (i < parse_data.y)
	{
		scene_data->map[i] = malloc(parse_data.x * sizeof(char));
		if (scene_data->map[i] == NULL)
			exit(EXIT_FAILURE);
		while (j < parse_data.x)
		{
			scene_data->map[i][j] = parse_data.map[i][j];
			++j;
		}
		++i;
		j = 0;
	}
}

void	initialize_data(t_scene_data *scene_data, t_data parse_data)
{
	scene_data->altom = parse_data.y;
	scene_data->anchom = parse_data.x;
	scene_data->character = NULL;
	scene_data->ply = malloc(sizeof(t_player_data));
	if (scene_data->ply == NULL)
	{
		free(scene_data->ply);
		exit(EXIT_FAILURE);
	}
	scene_data->ply->x = 200.0;
	scene_data->ply->y = 200.0;
	scene_data->ply->rot_angle = 2.0 * M_PI / 2;
	scene_data->ply->move_step = SPEED;
	scene_data->ply->rot_step = TURN * (M_PI / 180);
	scene_data->ray = malloc(WIDTH * sizeof(t_ray_data));
	if (scene_data->ray == NULL)
	{
		free(scene_data->ray);
		exit(EXIT_FAILURE);
	}
	reserve_memory_map(scene_data, parse_data);
	initialize_ray(scene_data);
}
