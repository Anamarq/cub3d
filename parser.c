/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:10:50 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/17 17:48:42 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_data_struct(t_data *data)
{
    data->fd = -1;
    data->error = NO_ERROR;
    data->pipeline = NULL;
    data->no = NULL;
    data->so = NULL;
    data->we = NULL;
    data->ea = NULL;
    data->floor = (t_color){0,0,0};
    data->ceiling = (t_color){0,0,0};
}

int check_params(int argc, const char **argv, t_data *data)
{
    int fd;
    
    if (argc == 1 || argc > 2)
    {
        data->error = ERROR_ARGMTS;
        return (1);
    }
    else
    {
        fd = open(argv[1], O_RDWR);
        if (fd == -1)
        {
            data->error = ERROR_FILE;
            return (1);
        }
        else
            data->fd = fd;
    }
    return (0);
}

int is_file_empty(char *line, t_data *data)
{
    if (!line)
    {
        data->error = ERROR_FILE_EMPTY;
        return (1);
    }
    return (0);
}

/*int discard_empty_lines(t_data *data)
{
    
}*/

int check_map_file(t_data *data)
{
    char *line;
    
    line = get_next_line(data->fd);
    if (is_file_empty(line, data) == 1)
        return (1);
    while(line)
    {
        
    }
    return (0);
}
