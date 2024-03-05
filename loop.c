/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calcula la nueva x o nueva y según donde se pulse
void	calculate_new_coordinates(double *newx, double *newy, t_scene_data *sd)
{
	if (mlx_is_key_down(sd->mlx, MLX_KEY_W))
	{
		*newx = sd->ply->x + cos(sd->ply->rot_angle) * sd->ply->move_step;
		*newy = sd->ply->y + sin(sd->ply->rot_angle) * sd->ply->move_step;
	}
	if (mlx_is_key_down(sd->mlx, MLX_KEY_S))
	{
		*newx = sd->ply->x - cos(sd->ply->rot_angle) * sd->ply->move_step;
		*newy = sd->ply->y - sin(sd->ply->rot_angle) * sd->ply->move_step;
	}
	if (mlx_is_key_down(sd->mlx, MLX_KEY_D))
	{
		*newx = sd->ply->x + cos(sd->ply->rot_angle
				+ (M_PI / 2)) * sd->ply->move_step;
		*newy = sd->ply->y + sin(sd->ply->rot_angle
				+ (M_PI / 2)) * sd->ply->move_step;
	}
	if (mlx_is_key_down(sd->mlx, MLX_KEY_A))
	{
		*newx = sd->ply->x + cos(sd->ply->rot_angle
				- (M_PI / 2)) * sd->ply->move_step;
		*newy = sd->ply->y + sin(sd->ply->rot_angle
				- (M_PI / 2)) * sd->ply->move_step;
	}
}

//actualiza el angulo de rotacion
//si no choca se actualiza
//por ultimo se calculan los rayos (inicio de raycasting)
void	ft_hook(void *param)
{
	t_scene_data	*sd;
	double			newx;
	double			newy;

	sd = param;
	newx = sd->ply->x;
	newy = sd->ply->y;
	calculate_new_coordinates(&newx, &newy, sd);
	if (mlx_is_key_down(sd->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(sd->mlx);
	if (mlx_is_key_down(sd->mlx, MLX_KEY_LEFT))
		sd->ply->rot_angle -= sd->ply->rot_step;
	if (mlx_is_key_down(sd->mlx, MLX_KEY_RIGHT))
		sd->ply->rot_angle += sd->ply->rot_step;
	if (!player_colision(sd->map, newx, newy))
	{
		sd->character->instances[0].x = newx / (TILE / 10);
		sd->ply->x = newx;
		sd->character->instances[0].y = newy / (TILE / 10);
		sd->ply->y = newy;
	}
	sd->ply->rot_angle = normalize_angle(sd->ply->rot_angle);
	calculate_ray(sd);
}
