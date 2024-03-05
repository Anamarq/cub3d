/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

//XIntercept es la siguiente x horiz
//Bucle para buscar punto de colision. Mientras no haya un choque
//tile_x, y Obtenemos la casilla redondeando por abajo
//Si hay colision se asigna wallHitX Si no, avanzamos a la siguiente casilla
int	loop_colision_horiz(t_colision_data col_data, t_ray_data *ray,
		t_scene_data *sd)
{
	int	next_x;
	int	next_y;
	int	tile_x;
	int	tile_y;

	next_x = col_data.x_intercept;
	next_y = col_data.y_intercept;
	while ((next_x >= 0 && next_y >= 0
			&& next_x < sd->anchom * TILE && next_y < sd->altom * TILE))
	{
		tile_x = (int)(next_x / TILE);
		tile_y = (int)(next_y / TILE);
		if (scene_colision(sd, tile_x, tile_y))
		{
			ray->wall_hit_x_horiz = next_x;
			ray->wall_hit_y_horiz = next_y;
			return (1);
		}
		else
		{
			next_x += col_data.x_step;
			next_y += col_data.y_step;
		}
	}
	return (0);
}

//y_intercept Buscar primera interseccion. y2
//Si apunta hacia abajo incrementamos un tile
//La y del triangulo que se forma dif entre y2 - y1. xady=(y2-y1)/tan(angulo)
//adyacente = (yIntercept - sd->ray->y) / tan(sd->ray->ray_angle);
//y step, s xtep: Calculamos distancia de cada paso, tile
//Si vamos hacia arriba, invertir paso Y
//Comprobamos que el paso x es coherente
//Si va a la izquierda no puede ser mayor que 0
//Si apunta hacia arriba, resto un pixel para forzar la colision con
//la casilla, sino falsa colision
int	horizontal_colision(int down, int left, t_ray_data *ray, t_scene_data *sd)
{
	t_colision_data	col_data;

	col_data.x_intercept = 0;
	col_data.y_intercept = 0;
	col_data.x_step = 0;
	col_data.y_step = 0;
	col_data.y_intercept = floor(ray->y / TILE) * TILE;
	if (down)
		col_data.y_intercept += TILE;
	col_data.x_intercept = (col_data.y_intercept - ray->y)
		/ tan(ray->ray_angle) + ray->x;
	col_data.y_step = TILE;
	col_data.x_step = col_data.y_step / tan(ray->ray_angle);
	if (!down)
		col_data.y_step = -col_data.y_step;
	if ((left && col_data.x_step > 0) || (!left && col_data.x_step < 0))
		col_data.x_step = -col_data.x_step;
	if (!down)
		--col_data.y_intercept;
	return (loop_colision_horiz(col_data, ray, sd));
}

//XIntercept es la siguiente x vert
//Bucle para buscar punto de colision. Mientras no haya un choque
//tile_x, y Obtenemos la casilla redondeando por abajo
//Si hay colision se asigna wallHitX Si no, avanzamos a la siguiente casilla
int	loop_colision_vert(t_colision_data col_data, t_ray_data *ray,
	t_scene_data *sd)
{
	int	next_x;
	int	next_y;
	int	tile_x;
	int	tile_y;

	next_x = col_data.x_intercept;
	next_y = col_data.y_intercept;
	while ((next_x >= 0 && next_y >= 0 && next_x < sd->anchom * TILE
			&& next_y < sd->altom * TILE))
	{
		tile_x = (int)(next_x / TILE);
		tile_y = (int)(next_y / TILE);
		if (scene_colision(sd, tile_x, tile_y))
		{
			ray->wall_hit_x_vert = next_x;
			ray->wall_hit_y_vert = next_y;
			return (1);
		}
		else
		{
			next_x += col_data.x_step;
			next_y += col_data.y_step;
		}
	}
	return (0);
}

//x_intercept Buscar primera interseccion. x2
//Si apunta hacia derecha incrementamos un tile
//se suma el cateto opuesto
//double opuesto = (col_data.x_intercept - sd->ray->x) * tan(sd->ray->ray_angle)
//y step, s xtep: Calculamos distancia de cada paso, tile
//Si vamos hacia izq, invertir paso x
//Comprobamos que el paso y es coherente
//Si va a la arriba no puede ser mayor que 0
//Si apunta hacia izq, resto un pixel para forzar
//la colision con la casilla, sino falsa colision
int	vertical_colision(int down, int left, t_ray_data *ray, t_scene_data *sd)
{
	t_colision_data	col_data;

	col_data.x_intercept = 0;
	col_data.y_intercept = 0;
	col_data.x_step = 0;
	col_data.y_step = 0;
	col_data.x_intercept = floor(ray->x / TILE) * TILE;
	if (!left)
		col_data.x_intercept += TILE;
	col_data.y_intercept = (col_data.x_intercept - ray->x)
		* tan(ray->ray_angle) + ray->y;
	col_data.x_step = TILE;
	col_data.y_step = col_data.x_step * tan(ray->ray_angle);
	if (left)
		col_data.x_step = -col_data.x_step;
	if ((!down && col_data.y_step > 0) || (down && col_data.y_step < 0))
		col_data.y_step = -col_data.y_step;
	if (left)
		col_data.x_intercept--;
	return (loop_colision_vert(col_data, ray, sd));
}
