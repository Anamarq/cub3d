/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colisions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:53 by anamarqu          #+#    #+#             */
/*   Updated: 2024/02/02 13:04:55 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

//Averiguar si choca
int	scene_colision(char **matriz, int x, int y)
{
	int	choca;

	choca = 0;
	if (matriz[y][x] == '1')
		choca = 1;
	return (choca);
}

//Averiguar en que casilla estamos
//casillax La pos en pixels. pos en la que estoy entre el ancho de cada casilla
//ya casillaX/Y estara en valores de la matriz, solo hay que mirar si es 0 o 1
int	player_colision(char **matrix, double x, double y)
{
	int	choca;
	int	casillax;
	int	casillay;

	choca = 0;
	casillax = (int)(x / TILE);
	casillay = (int)(y / TILE);
	if (scene_colision(matrix, casillax, casillay))
		choca = 1;
	return (choca);
}
