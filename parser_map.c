/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:19:33 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/06 12:56:01 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill(char **tab, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= size.y + 2 || cur.x < 0 || cur.x >= size.x
		+ 2 || (tab[cur.y][cur.x] != to_fill && tab[cur.y][cur.x] != ' '))
		return ;
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

int	 is_map_start(char *line, t_data data)
{
	size_t	i;
	size_t	len;

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

static int	is_player(char c)
{
	if ((c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (1);
	return (0);
}

t_point	find_person(char **map, t_point size)
{
	int		i;
	size_t	j;
	int		found;
	t_point	person;

	person = (t_point){-1, -1};
	found = 0;
	i = -1;
	while (i++ < size.y)
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			if (is_player(map[i][j]) && !found)
			{
				person = (t_point){j, i};
				found = 1;
			}
			else if (is_player(map[i][j]) && found)
				return ((t_point){-2, -2});
			j++;
		}
	}
	return (person);
}
