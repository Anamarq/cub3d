/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:44:21 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/06 12:29:45 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*fill_with_spaces(int size)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc(size + 3);
	while (j < size + 2)
	{
		new[j] = ' ';
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*add_line(char *line, int size)
{
	int		j;
	char	*new;

	new = malloc(size + 3);
	j = 0;
	while (j < size + 2)
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
	return (new);
}

char	**copy_and_encase_map(char **map, t_point size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (size.y + 3));
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

int	is_map_correct(t_data *data, t_point size)
{
	char	**new;
	t_point	zero;

	new = copy_and_encase_map(data->map, size);
	zero = find_first_zero(new, size);
	while (zero.x != -1)
	{
		flood_fill(new, size, zero);
		if (is_map_different(new, data->map, size))
		{
			data->error = INVALID_CHAR;
			ft_free_array(new);
			return (0);
		}
		zero = find_first_zero(new, size);
	}
	ft_free_array(data->map);
	data->map = new;
	return (1);
}

int	is_map_line_correct(char *line, t_data *data)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(line);
	while (i < n)
	{
		if (is_invalid_char_in_map(line, n))
		{
			data->error = INVALID_CHAR_IN_LINES;
			free(line);
			return (0);
		}
		i++;
	}
	return (1);
}
