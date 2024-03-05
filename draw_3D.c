/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/03/05 17:34:38 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Devuelve el color en formato int32_t
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//Crea una imagen a partir de una textura
mlx_image_t	*create_img(mlx_t *mlx, char *route)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(route);
	if (!texture)
		error(mlx);
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error(mlx);
	mlx_delete_texture(texture);
	return (img);
}

//crea las imagenes de textura y las guarda em el struct
void	create_walls(t_scene_data *sd, t_data data)
{
	printf("%s\n", data.ea);
	sd->walls.tx_right = create_img(sd->mlx, data.ea);
	if (!(sd->walls.tx_right))
		error(sd->mlx);
	printf("%s\n", data.we);
	sd->walls.tx_left = create_img(sd->mlx, data.we);
	if (!(sd->walls.tx_left))
		error(sd->mlx);
	printf("%s\n", data.no);
	sd->walls.tx_up = create_img(sd->mlx, data.no);
	if (!(sd->walls.tx_up))
		error(sd->mlx);
	printf("%s\n", data.so);
	sd->walls.tx_down = create_img(sd->mlx, data.so);
	if (!(sd->walls.tx_down))
		error(sd->mlx);
}

//Dibuja el cielo y el suelo
//skc sky color, fc floor color
void	draw_background(t_color skc, t_color fc, mlx_t *mlx)
{
	mlx_image_t	*backgrnd;
	uint32_t	x;
	uint32_t	y;

	backgrnd = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!(backgrnd))
		error(mlx);
	x = -1;
	y = 0;
	while (++x < backgrnd->width)
	{
		while (y < backgrnd->height / 2)
		{
			mlx_put_pixel(backgrnd, x, y, ft_pixel(skc.r, skc.g, skc.b, 255));
			++y;
		}
		while (y < backgrnd->height)
		{
			mlx_put_pixel(backgrnd, x, y, ft_pixel(fc.r, fc.g, fc.b, 255));
			++y;
		}
		y = 0;
	}
	if (mlx_image_to_window(mlx, backgrnd, 0, 0) == -1)
		error(mlx);
}

//Dibuja la escena 3D
void	draw_3d(t_scene_data *scene_data)
{
	scene_data->scene = mlx_new_image(scene_data->mlx, WIDTH, HEIGHT);
	if (!(scene_data->scene))
		error(scene_data->mlx);
	if (mlx_image_to_window(scene_data->mlx, scene_data->scene, 0, 0) == -1)
		error(scene_data->mlx);
}
