/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:57:42 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/05 14:58:56 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_info_lines(char *line, t_data *data)
{
	while (line && !is_map_start(line, *data))
	{
		if (!is_line_correct(data, line))
			return (NULL);
		free(line);
		line = get_next_line(data->fd);
	}
	return (line);
}

char	*get_lines_after_map(char *line, t_data *data)
{
	while (line && is_all_spaces(line))
	{
		free(line);
		line = get_next_line(data->fd);
	}
	if (line && !is_all_spaces(line))
	{
		free(line);
		data->error = EMPTY_LINE_IN_MAP;
		return (NULL);
	}
	return (line);
}

static char	**split_map(t_data *data, char *line, char *input)
{
	char	**result;

	result = NULL;
	if (data->error == NO_ERROR)
	{
		result = ft_split(input, '\n');
		if (!result)
		{
			free(line);
			free(input);
			data->error = ERROR_FILE_EMPTY;
		}
	}
	return (result);
}

char	**get_file_input(t_data *data)
{
	char	*input;
	char	*line;
	char	**result;

	input = NULL;
	line = get_next_line(data->fd);
	if (is_file_empty(line, data) == 1)
		return (NULL);
	line = get_info_lines(line, data);
	if (!line)
		return (NULL);
	while (line && !is_all_spaces(line))
	{
		if (!is_map_line_correct(line, data))
			return (NULL);
		input = ft_join_free(input, line);
		free(line);
		line = get_next_line(data->fd);
	}
	line = get_lines_after_map(line, data);
	result = split_map(data, line, input);
	return (free(line), free(input), result);
}
