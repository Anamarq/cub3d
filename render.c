/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcula el índice del píxel en el buffer de píxeles
// Se multiplica por 4 para tener en cuenta los 4 bytes por píxel (RGBA)
//Accede al buffer de píxeles y combina los valores de RGBA en un solo uint32_t
uint32_t	get_pixel_color(int x, int y, mlx_image_t *tx)
{
	int			index;
	uint32_t	color;

	index = (y * tx->width + x) * 4;
	color = (tx->pixels[index] << 24) | (tx->pixels[index + 1] << 16)
		| (tx->pixels[index + 2] << 8) | tx->pixels[index + 3];
	return (color);
}

//elige la textura segun la direccion
mlx_image_t	*choose_tx(t_scene_data *sd, int n)
{
	if (n == 0)
		return (sd->walls.tx_right);
	else if (n == 1)
		return (sd->walls.tx_left);
	else if (n == 2)
		return (sd->walls.tx_up);
	else if (n == 3)
		return (sd->walls.tx_down);
	return (NULL);
}

//y0, y1 Calculamos donde empieza y acaba la línea
//y0 mitad pantalla - mitad muro
//y1 donde acaba
//la y0aux, y1aux es para la línea real, que se sale de la pantalla.
//la y0, y1 es la línea que se dibuja, que se limita para que no de segfault
//en el bucle se hace una regla de 3 para elegir el pixel de textura y.
//el bucle dibuja la linea
void	render_wall(t_scene_data *sd, t_ray_data ray)
{
	t_render_data	rd;
	int				y;
	uint32_t		color;

	rd.plane_distance = (WIDTH / 2) / tan(FOV / 2.0);
	rd.hight_wall = (TILE * 10 / ray.distance) * rd.plane_distance;
	rd.y0 = (int)(HEIGHT / 2) - (int)(rd.hight_wall / 2);
	rd.y1 = rd.y0 + rd.hight_wall;
	rd.x = ray.columna;
	rd.y0aux = rd.y0;
	rd.y1aux = rd.y1;
	if (rd.y0 >= HEIGHT)
		rd.y0 = HEIGHT - 1;
	if (rd.y1 < 0)
		rd.y1 = 0;
	y = rd.y1;
	while (y < rd.y0)
	{
		rd.py = TILE * (y - rd.y1aux) / (rd.y0aux - rd.y1aux);
		color = get_pixel_color(ray.pixel_texturex, rd.py,
				choose_tx(sd, ray.direction));
		mlx_put_pixel(sd->scene, rd.x, y, color);
		++y;
	}
}

// Establecer el píxel en negro
//es necesario para actualizar la imagen, como limpiar el buffer
void	clear_screen(mlx_image_t *scene)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (x < WIDTH)
	{
		while (i < HEIGHT)
		{
			mlx_put_pixel(scene, x, i, 0x000000);
			++i;
		}
		i = 0;
		++x;
	}
}

//para cada rayo:
//se calcula el angulo actual
//tras el cast: Correccion ojo de pez
//se calcula donde se dibuja el end en el minimapa
void	calculate_ray(t_scene_data *sd)
{
	int	xdest;
	int	ydest;
	int	i;

	clear_screen(sd->scene);
	i = 0;
	while (i < WIDTH)
	{
		sd->ray[i].ray_angle = normalize_angle(sd->ply->rot_angle
				+ sd->ray[i].step_angle);
		sd->ray[i].x = sd->ply->x;
		sd->ray[i].y = sd->ply->y;
		cast(&sd->ray[i], sd);
		sd->ray[i].distance = sd->ray[i].distance * cos(sd->ply->rot_angle
				- sd->ray[i].ray_angle);
		render_wall(sd, sd->ray[i]);
		xdest = sd->ray[i].wall_hit_x;
		ydest = sd->ray[i].wall_hit_y;
		sd->end->instances[i].x = xdest / (TILE / 10);
		sd->end->instances[i].y = ydest / (TILE / 10);
		++i;
	}
}
