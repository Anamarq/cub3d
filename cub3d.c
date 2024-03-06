/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:37:08 by anamarqu          #+#    #+#             */
/*   Updated: 2024/03/06 13:28:39 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leaks(void)
{
	system("leaks -q cub3d");
}

void	free_memory(t_scene_data *sd)
{
	int	i;

	i = 0;
	free(sd->ply);
	free(sd->ray);
	while (i < sd->altom)
	{
		free(sd->map[i]);
		++i;
	}
	free(sd->map);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_data			data;
	t_scene_data	sd;

	atexit(leaks);
	parser(argc, argv, &data);
	initialize_data(&sd, data);
	set_graphics(&sd, data);
	free_memory(&sd);
	free_struct(&data);
	return (EXIT_SUCCESS);
}
