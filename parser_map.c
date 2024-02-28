/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:19:33 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/26 21:11:10 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill(char **tab, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y + 2 || cur.x < 0 || cur.x >= size.x + 2
		|| (tab[cur.y][cur.x] != to_fill && tab[cur.y][cur.x] != ' '))
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
	if (data.no && data.so && data.we && data.ea && data.floor.r != -1
		&& data.floor.g != -1 && data.floor.b != -1 && data.ceiling.r != -1
		&& data.ceiling.g != -1 && data.ceiling.b != -1)
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
			data->error = INVALID_CHAR_IN_LINES;
			//printf("Es aquí en linea [%s]\n", line);
			free(line);
			return (0);
		}
		i++;
	}
	return (1);
}

t_point get_size(char **map)
{
	size_t i;
	size_t j;
	size_t n;
	size_t m;
	size_t longest;
	
	n = ft_array_len(map);
	i = 0;
	longest = 0;
	while (i < n)
	{
		j = 0;
		m = ft_strlen(map[i]);
		while(j < m)
		{
			j++;
			if (j > longest)
				longest = j;
		}
		i++;
	}
	return ((t_point){longest, i});
}

t_point find_person(char **map, t_point size)
{
	int i;
	size_t j;
	int found;
	t_point person;
	
	person = (t_point){-1, -1};
	found = 0;
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while(j < ft_strlen(map[i]))
		{
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && !found)
			{
				person = (t_point){j, i};
				found = 1;
			}
			else if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E') && found)
					return((t_point){-1, -1});
			j++;
		}
		i++;
	}
	return(person);
}
