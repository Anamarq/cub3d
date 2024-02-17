/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_txure_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:39:05 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/17 21:14:36 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_path_line(char *line)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        return (1);
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        return (1);
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        return (1);
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        return (1);
    return (0); 
}

static int is_color_line(char *line)
{
    if (line[0] == 'F' && line[1] == ' ')
        return (1);
    else if (line[0] == 'C' && line[1] == ' ')
        return (1);
    return (0); 
}

static int is_path_format(char *line)
{
    size_t i;
    size_t n;
    int fd;

    n = ft_strlen(line);
    i = 2;
    while(i < n && line[i] == ' ')
        i++;
    if (!line[i])
        return (0);
    if (line[i] == '.')
        fd = open(&line[i], O_RDONLY);
    else
        return (0);
    if (fd == -1)
        return (0);
    close(fd);
    return(1);
}

static int is_color_format(char *line)
{
    size_t i;
    size_t n;

    n = ft_strlen(line);
    i = 1;
    while(i < n && line[i] == ' ')
        i++;
    if (!line[i])
        return (0);
    return (1);
}

int is_line_correct(t_data *data, char *line)
{
    if (is_path_line(line))
    {
        if (!is_path_format(line))
            data->error = INVALID_CHAR;
    }
    else if (is_color_line(line))
    {
        if (!is_color_format(line))
            data->error = INVALID_CHAR;
    }
    else if (!is_all_spaces(line))
        data->error = INVALID_CHAR;
    if (data->error == INVALID_CHAR)
    {
        free (line);
        return (0);
    }
    return (1);
}
