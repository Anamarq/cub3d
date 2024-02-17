/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:10:50 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/17 16:43:04 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_data_struct(t_data *data)
{
    data->error = NO_ERROR;
    data->pipeline = NULL;
    data->no = NULL;
    data->so = NULL;
    data->we = NULL;
    data->ea = NULL;
    data->floor = (t_color){0,0,0};
    data->ceiling = (t_color){0,0,0};
}

int check_params(int argc, char *argv, t_data *data)
{
    int fd;
    
    if (argc > 2)
    {
        data->error = ERROR_ARGMTS;
        return (1);
    }
    else
    {
        fd = open(argv[1]);
        if (fd == -1)
        {
            data->error = ERROR_FILE;
            return (1);
        }
    }
    return (0);
}