/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:10:50 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/06 15:21:36 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data_struct(t_data *data)
{
	data->fd = -1;
	data->error = NO_ERROR;
	data->pipeline = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor = (t_color){-1, -1, -1};
	data->ceiling = (t_color){-1, -1, -1};
	data->x = -1;
	data->y = -1;
}

int	check_params(int argc, char **argv, t_data *data)
{
	int	n;

	if (argc == 1 || argc > 2)
	{
		data->error = ERROR_ARGMTS;
		return (1);
	}
	else
	{
		n = ft_strlen(argv[1]);
		if (ft_strcmp(&argv[1][n - 4], ".cub") != 0)
		{
			data->error = ERROR_FILE_TYPE;
			return (1);
		}
		data->fd = open(argv[1], O_RDWR);
		if (data->fd == -1)
		{
			data->error = ERROR_FILE;
			return (1);
		}
	}
	return (0);
}

int	is_file_empty(char *line, t_data *data)
{
	if (!line)
	{
		data->error = ERROR_FILE_EMPTY;
		return (1);
	}
	return (0);
}

int	is_line_correct(t_data *data, char *line)
{
	int	type;

	type = is_path_line(line);
	if (type)
	{
		if (!is_path_format(line, type, data))
			data->error = ERROR_NO_PATHS;
	}
	else
	{
		type = is_color_line(line);
		if (type)
		{
			if (!is_color_format(line, type, data))
				data->error = ERROR_NO_COLOR;
		}
		else if (!is_all_spaces(line))
			data->error = INVALID_CHAR_IN_LINES;
	}
	if (data->error != NO_ERROR)
	{
		free(line);
		return (0);
	}
	return (1);
}
