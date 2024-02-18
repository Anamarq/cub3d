/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_txure_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:39:05 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/18 17:46:12 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>

int is_path_line(char *line)
{
    if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        return (1);
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        return (2);
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        return (3);
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        return (4);
    return (0); 
}

static void set_type(int type, char *path, t_data *data)
{
    if (type == 1)
        data->no = ft_strdup(path);
    else if (type == 2)
        data->so = ft_strdup(path);
    else if (type == 3)
        data->we = ft_strdup(path);
    else if (type == 4)
        data->ea = ft_strdup(path);
}

int is_path_format(char *line, int type, t_data *data)
{
    size_t i;
    size_t n;
    int fd;
    char *file;

    n = ft_strlen(line);
    i = 2;
    while(i < n && line[i] == ' ')
        i++;
    if (!line[i])
        return (0);
    file = ft_substr(line, i, (n - 1) - i);
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("no abre archivo %d\n", errno);
        return (0);
    }
    close(fd);
    set_type(type, &line[i], data);
    return(1);
}
