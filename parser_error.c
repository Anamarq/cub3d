/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:38:21 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/17 18:33:28 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_error(t_data data)
{
    if (data.error == ERROR_ARGMTS)
        write(2, "El número de argumentos no es correcto\n", 39);
    else if (data.error == ERROR_FILE)
        write(2, "El archivo no existe o está corrupto\n", 37);
    else if (data.error == ERROR_FILE_EMPTY)
        write(2, "El archivo está vacío\n", 23);
}


void debug_map_content(char **content)
{
    int n = ft_array_len(content);
    int i = 0;
    while (i < n)
    {
        printf("%s\n",content[i]);
        i++;
    }
}