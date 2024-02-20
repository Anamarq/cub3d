/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/20 18:27:03 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
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
	t_point size = get_size(data.map);
	printf("size: %i, %i\n",size.x, size.y);
	t_point begin = find_person(data.map, size);
	t_point zero = find_first_zero(data.map, size);
	printf("begin: %i, %i\n",begin.x, begin.y);

	char **new = copy_map(data.map, size);
	
	printf("caracter [%c]\n", new[2][8]);
	flood_fill(new, size, zero);
	
	write(1, "sale de floodfill\n", 18);
	print_map_content(data.map);
	print_map_content(new);
	if (is_f_outside(new, size) || is_map_different(new, data.map, size))
		printf("El mapa está mal\n");
	else
		printf("El mapa está bien\n");
	//print_struct_content(data);
	ft_free_array(new);
	close(data.fd);
	free_struct(&data);
    return (0);
}
