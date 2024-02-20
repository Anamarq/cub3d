/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:14:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/20 17:39:48 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **copy_map(char **map, t_point size)
{
    char **new;
    int i;
    int j;
    
    new = malloc(sizeof(char*) * size.y + 1);
	i = 0;
	while (i < size.y)
	{
		new[i] = malloc(size.x + 1);
		j = 0;
		while(j < size.x)
		{
			new[i][j] = map[i][j];
			j++;
		}
		new[i][size.x] = '\0';
		i++;
	}
	new[i] = 0;
    return (new);
}

t_point find_first_zero(char **map, t_point size)
{
	int i;
	int j;
	
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while(j < size.x)
		{
			if (map[i][j] == '0')
				return ((t_point){j, i});
			j++;
		}
		i++;
	}
	return((t_point){-1, -1});
}

int is_map_different(char **copy, char **map, t_point size)
{
	int i;
    int j;
    
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while(j < size.x)
		{
			if (map[i][j] == ' ' && copy[i][j] == 'F')
				return (1);
			j++;
		}
		i++;
	}
    return (0);
}

int is_f_outside(char **copy, t_point size)
{
	int i;
    int j;
    
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while(j < size.x)
		{
			if (i == 0 && copy[i][j] == 'F')
				return (1);
			else if (i == size.y - 1 && copy[i][j] == 'F')
				return (1);
			else if (j == 0 - 1 && copy[i][j] == 'F')
				return (1);
			else if (j == size.x - 1 && copy[i][j] == 'F')
				return (1);
			else if (copy[i][j] == 'F' && copy[i - 1][j] == ' ')
				return (1);
			else if (copy[i][j] == 'F' && copy[i + 1][j] == ' ')
				return (1);
			j++;
		}
		i++;
	}
    return (0);
}
