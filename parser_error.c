/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:38:21 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/05 14:16:13 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_data data)
{
	write(2, "Error\n", 6);
	if (data.error == ERROR_ARGMTS)
		write(2, "El número de argumentos no es correcto\n", 39);
	else if (data.error == ERROR_FILE_TYPE)
		write(2, "El tipo de archivo no se permite\n", 33);
	else if (data.error == ERROR_FILE)
	{
		write(2, "El archivo no existe o está corrupto\n", 37);
		close(data.fd);
	}
	else if (data.error == ERROR_FILE_EMPTY)
	{
		write(2, "El archivo está vacío\n", 23);
		close(data.fd);
	}
	else if (data.error == INVALID_CHAR_IN_LINES)
	{
		write(2, "Carácter no válido\n", 20);
		close(data.fd);
	}
	else if (data.error == EMPTY_LINE_IN_MAP)
		write(2, "Línea vacía dentro del mapa\n", 29);
	exit(1);
}

void	ft_error_file_content(t_data *data)
{
	write(2, "Error\n", 6);
	if (data->error == INVALID_CHAR)
		write(2, "El mapa no es válido\n", 21);
	close(data->fd);
	free_struct(data);
	exit(1);
}

void	print_map_content(char **content)
{
	int	n;
	int	i;

	n = ft_array_len(content);
	i = 0;
	printf("/**** MAP CONTENT ****/\n");
	while (i < n)
	{
		printf("linea: [%s]\n", content[i]);
		i++;
	}
}

void	print_struct_content(t_data data)
{
	printf("/**** STRUCT CONTENT ****/\n");
	printf("NO: %s\n", data.no);
	printf("SO: %s\n", data.so);
	printf("WE: %s\n", data.we);
	printf("EA: %s\n", data.ea);
	printf("F: %i,%i,%i\n", data.floor.r, data.floor.g, data.floor.b);
	printf("C: %i,%i,%i\n", data.ceiling.r, data.ceiling.g, data.ceiling.b);
}
