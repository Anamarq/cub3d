/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:44:21 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/23 18:56:09 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_map_correct(t_data *data, t_point size)
{
    char **new;
    t_point zero;
	
	//print_map_content(data->map);
	new = copy_and_encase_map(data->map, size);
	zero = find_first_zero(new, size);
	while(zero.x != -1)
	{
		flood_fill(new, size, zero);
		
		//print_map_content(new);
		if (is_map_different(new, data->map, size))
        {
            data->error = INVALID_CHAR;
            ft_free_array(new);
			return (0);
        }
		zero = find_first_zero(new, size);
	}
    ft_free_array(new);
    return (1);
}
