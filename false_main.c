/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/18 17:48:36 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, const char **argv)
{
    t_data data;

	init_data_struct(&data);
	if (check_params(argc, argv, &data) != 0)
	{
		ft_error(data);
		exit(-1);
	}
	data.map = get_file_input(&data);
	if (data.error != NO_ERROR)
	{
		ft_error(data);
		close(data.fd);
		free_struct(&data);
		exit(-1);
	}
	print_map_content(data.map);
	print_struct_content(data);
	close(data.fd);
	free_struct(&data);
    return (0);
}
