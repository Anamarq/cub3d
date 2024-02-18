/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:19:33 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/18 17:55:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill(char **tab, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| tab[cur.y][cur.x] != to_fill)
		return;

	tab[cur.y][cur.x] = 'F';
	fill(tab, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(tab, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);
}

int is_map_start(char *line, t_data data)
{
	size_t i;
	size_t len;

	//printf("comprueba [%s]\n",line);
	i = 0;
	len = ft_strlen(line);
	if (data.no && data.so && data.we && data.ea && data.floor.r
		&& data.floor.g && data.floor.b && data.ceiling.r
		&& data.ceiling.g && data.ceiling.b)
	{
		while (i < len && line[i] == ' ')
			i++;
		if (line[i] == '1')
			return (1);
	}
	return (0);
}

int is_map_line_correct(char *line, t_data *data)
{
	size_t i;
	size_t n;

	i = 0;
	n = ft_strlen(line);
	while (i < n)
	{
		if (is_invalid_char_in_map(line, n))
		{
			data->error = INVALID_CHAR;
			return (0);
		}
		i++;
	}
	return (1);
}
