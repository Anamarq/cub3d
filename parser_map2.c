/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:14:03 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/23 18:52:04 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *fill_with_spaces(int size)
{
	int j;
	char *new;
	
	j = 0;
	new = malloc(size + 3);
	while(j < size + 2)
	{
		new[j] = ' ';
		j++;
	}
	new[j] = '\0';
	return(new);
	
}

char *add_line(char *line, int size)
{
	int j;
	char *new;
	
	new = malloc(size + 3);
	j = 0;
	while(j < size + 2)
	{
		if (j == 0)
			new[j] = ' ';
		else if ((size_t)j <= ft_strlen(line))
			new[j] = line[j - 1];
		else
			new[j] = ' ';
		j++;
	}
	new[j] = '\0';
	return(new);
}

char **copy_and_encase_map(char **map, t_point size)
{
    char **new;
    int i;
    
    new = malloc(sizeof(char*) * (size.y + 3));
	new[0] = fill_with_spaces(size.x);
	i = 1;
	while (i <= size.y)
	{
		new[i] = add_line(map[i - 1], size.x);
		i++;
	}
	new[i] = fill_with_spaces(size.x);
	i += 1;
	new[i] = 0;
    return (new);
}

char *copy_line(char *line, int size)
{
	int j;
	char *new;
	
	new = malloc(size + 3);
	j = 0;
	while(j < size + 2)
	{
		new[j] = line[j];
		j++;
	}
	new[j] = '\0';
	return(new);
}

t_point find_first_zero(char **map, t_point size)
{
	int i;
	int j;
	
	i = 0;
	while (i < size.y + 1)
	{
		j = 0;
		while(j < size.x + 1)
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
    
	j = 0;
	while(j < size.x + 2)
	{
		if (copy[0][j] == 'F')
			return(1);
		j++;
	}
	i = 1;
	while (i < size.y)
	{
		j = 0;
		while(j < size.x)
		{
			if (map[i][j] == ' ' && copy[i + 1][j + 1] == 'F')
				return (1);
			j++;
		}
		i++;
	}
	j = 0;
	while(j < size.x + 2)
	{
		if (copy[size.y][j] == 'F')
			return(1);
		j++;
	}
    return (0);
}
