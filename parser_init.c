/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:10:50 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/20 20:24:44 by ljustici         ###   ########.fr       */
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
    data->floor = (t_color){-1,-1,-1};
    data->ceiling = (t_color){-1,-1,-1};
}

int check_params(int argc, char **argv, t_data *data)
{
    int fd;
    int n;
    
    
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
            data->error = ERROR_FILE;
            return (1);
        }
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

int is_line_correct(t_data *data, char *line)
{
    int type;
    
    //printf("linea: [%s]\n", line);
    type = is_path_line(line);
    if (type)
    {
        
        if (!is_path_format(line, type, data))
            data->error = INVALID_CHAR;
    }
    else
    {
        type =is_color_line(line);
        if (type)
        {
            if (!is_color_format(line, type, data))
                data->error = INVALID_CHAR;
        }
        else if (!is_all_spaces(line))
            data->error = INVALID_CHAR;
    }
    
    if (data->error == INVALID_CHAR)
    {
        printf("linea de error [%s]\n", line);
        free (line);
        return (0);
    }
    return (1);
}

char **get_file_input(t_data *data)
{
    char *input;
    char *line;
    char **result;
    
    result = NULL;
    input = NULL;
    line = get_next_line(data->fd);
    if (is_file_empty(line, data) == 1)
        return (NULL);
    /** TEXTURE AND COLOR **/
    while(line && !is_map_start(line, *data))
    {
        //printf("linea [%s]\n", line);
        if (!is_line_correct(data, line))
           break;
        free(line);
        line = get_next_line(data->fd);
    }
    /** SAVE MAP **/
    while (line)
    {
        if (!is_map_line_correct(line, data))
            break;
        input = ft_join_free(input, line);
        free(line);
        line = get_next_line(data->fd);
    }
    if (data->error == NO_ERROR)
    {
        result = ft_split(input, '\n');
        if (!result)
            data->error = ERROR_FILE_EMPTY;
    }
    free(input);
    return (result);
}
