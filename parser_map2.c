/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:14:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/05 13:37:10 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	find_first_zero(char **map, t_point size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y + 1)
	{
		j = 0;
		while (j < size.x + 1)
		{
			if (map[i][j] == '0')
				return ((t_point){j, i});
			j++;
		}
		i++;
	}
	return ((t_point){-1, -1});
}

static int	is_first_line_diff(t_point size, char **copy)
{
	int	j;

	j = 0;
	while (j < size.x + 2)
	{
		if (copy[0][j] == 'F')
			return (1);
		j++;
	}
	return (0);
}

static int	is_last_line_diff(t_point size, char **copy)
{
	int	j;

	j = 0;
	while (j < size.x + 2)
	{
		if (copy[size.y][j] == 'F')
			return (1);
		j++;
	}
	return (0);
}

int	is_map_different(char **copy, char **map, t_point size)
{
	int	i;
	int	j;

	j = 0;
	if (is_first_line_diff(size, copy))
		return (1);
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x + 2)
		{
			if (j >= (int)ft_strlen(map[i]) && copy[i + 1][j + 1] == 'F')
				return (1);
			else if (j < (int)ft_strlen(map[i]) && map[i][j] == ' ' && copy[i
					+ 1][j + 1] == 'F')
				return (1);
			j++;
		}
		i++;
	}
	is_last_line_diff(size, copy);
	return (0);
}

t_point	get_size(char **map, int len)
{
	int		i;
	size_t	j;
	size_t	m;
	size_t	longest;

	i = 0;
	longest = 0;
	while (i < len)
	{
		j = 0;
		m = ft_strlen(map[i]);
		while (j < m)
		{
			j++;
			if (j > longest)
				longest = j;
		}
		i++;
	}
	return ((t_point){longest, i});
}
