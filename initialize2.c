/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:40:15 by anamarqu          #+#    #+#             */
/*   Updated: 2024/03/05 13:40:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player2(t_scene_data *sd, int i, int j)
{
	sd->ply->x = j * TILE + TILE / 2;
	sd->ply->y = i * TILE + TILE / 2;
	if (sd->map[i][j] == 'N')
		sd->ply->rot_angle = 3.0 * M_PI / 2;
	if (sd->map[i][j] == 'S')
		sd->ply->rot_angle = M_PI / 2;
	if (sd->map[i][j] == 'E')
		sd->ply->rot_angle = 0;
	if (sd->map[i][j] == 'W')
		sd->ply->rot_angle = M_PI;
}

void	set_player(t_scene_data *sd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sd->altom)
	{
		while (j < sd->anchom)
		{
			if ((sd->map[i][j] == 'N') || (sd->map[i][j] == 'S')
				|| (sd->map[i][j] == 'E') || (sd->map[i][j] == 'W'))
			{
				set_player2(sd, i, j);
			}
			++j;
		}
		j = 0;
		++i;
	}
}

////Inicializar ventana
void	set_graphics(t_scene_data *sd, t_data data)
{
	set_player(sd);
	sd->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!(sd->mlx))
		error(sd->mlx);
	draw_background(data.ceiling, data.floor, sd->mlx);
	draw_3d(sd);
	draw_map2d(sd);
	draw_character2d(sd);
	draw_end(sd);
	create_walls(sd, data);
	mlx_loop_hook(sd->mlx, ft_hook, sd);
	mlx_loop(sd->mlx);
	mlx_terminate(sd->mlx);
}
