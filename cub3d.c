/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:49:03 by anamarqu          #+#    #+#             */
/*   Updated: 2024/03/06 13:49:04 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	parser(argc, argv, &data);
	initialize_data(&sd, data);
	set_graphics(&sd, data);
	free_memory(&sd);
	free_struct(&data);
	return (EXIT_SUCCESS);
}
