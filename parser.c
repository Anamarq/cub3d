/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/05 14:58:49 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	end_and_free_program(t_data *data)
{
	ft_error(*data);
	close(data->fd);
	free_struct(data);
	exit(-1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_point	size;
	t_point	player;

	init_data_struct(&data);
	if (check_params(argc, argv, &data) != 0)
		ft_error(data);
	data.map = get_file_input(&data);
	if (data.error != NO_ERROR)
		end_and_free_program(&data);
	size = get_size(data.map, ft_array_len(data.map));
	data.x = size.x;
	data.y = size.y;
	player = find_person(data.map, size);
	if (player.x == -1 && player.y == -1)
	{
		data.error = INVALID_CHAR;
		ft_error_file_content(&data);
	}
	if (!is_map_correct(&data, size))
		ft_error_file_content(&data);
	close(data.fd);
	free_struct(&data);
	return (0);
}
