/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/06 12:48:34 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static void	end_and_free_program(t_data *data)
{
	ft_error(*data);
	close(data->fd);
	free_struct(data);
	exit(-1);
}*/

int	parser(int argc, char **argv, t_data *data)
{
	t_point	size;
	t_point	player;

	init_data_struct(data);
	if (check_params(argc, argv, data) != 0)
		ft_error(*data);
	data->map = get_file_input(data);
	if (data->error != NO_ERROR)
		ft_error_file_content(data);
	size = get_size(data->map, ft_array_len(data->map));
	player = find_person(data->map, size);
	if (player.x < 0 && player.y < 0)
	{
		if (player.x == -1 && player.y == -1)
			data->error = ERROR_NO_PLAYER;
		else if (player.x == -2 && player.y == -2)
			data->error = ERROR_MANY_PLAYER;
		ft_error_file_content(data);
	}
	if (!is_map_correct(data, size))
		ft_error_file_content(data);
	size = get_size(data->map, ft_array_len(data->map));
	data->x = size.x;
	data->y = size.y;
	close(data->fd);
	return (0);
}
