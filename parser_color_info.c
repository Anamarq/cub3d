/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:27:07 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/20 20:22:04 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_atoible(char *word)
{
    size_t n;
    size_t j;

    j = 0;
    n = ft_strlen(word);
    while (j < n && word[j] == ' ')
        j++;
    while (j < n)
    {
        if (!ft_isdigit(word[j]) && word[j] != '\n')
            return (0);
        j++;
    }
    return (1);
}

static char** get_rgb_input(char *line)
{
    size_t i;
    size_t n;
    char **rgb;
    
    i = 1;
    n = ft_strlen(line);
    while(i < n && line[i] == ' ')
        i++;
    if (!line[i])
        return (NULL);
    rgb = ft_split(&line[i], ',');
    if (!rgb)
        return (NULL);
    n = ft_array_len(rgb);
    if (n == 3)
        return (rgb);
    return (NULL);
}

static void set_color(char **rgb, t_data *data, int type)
{
    int color[3];

    color[0] = ft_atoi(rgb[0]);
    color[1] = ft_atoi(rgb[1]);
    color[2] = ft_atoi(rgb[2]);
    if (type == 1)
        data->floor = (t_color){color[0], color[1], color[2]};
    else if (type == 2)
        data->ceiling = (t_color){color[0], color[1], color[2]};
}

int is_color_format(char *line, int type, t_data *data)
{
    size_t i;
    size_t n;
    char **rgb;
    int j;

    //printf("Entra el color format\n");
    rgb = get_rgb_input(line);
    if (!rgb)
        return (0);
    i = 0;
    j = 0;
    n = ft_array_len(rgb);
    while(i < n)
    {
        //printf("atoi [%i]\n", ft_atoi(rgb[i]));
        if (!is_atoible(rgb[i]))
        {
            printf("no es atoible[%s]\n", rgb[i]);
            return (0);
        }
        if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
            return (0);
        i++;
    }
    set_color(rgb, data, type);
    //printf("hizo setcolor\n");
    //printf("color guardardo %d\n", data->ceiling.r);
    ft_free_array(rgb);
    return (1);
}

int is_color_line(char *line)
{
    if (line[0] == 'F' && line[1] == ' ')
        return (1);
    else if (line[0] == 'C' && line[1] == ' ')
        return (2);
    return (0); 
}

