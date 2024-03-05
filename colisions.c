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

//Find out if it crashes
int	scene_colision(t_scene_data *sd, int x, int y)
{
	int	choca;

	choca = 0;
	if (y < sd->altom && y >= 0 && x < sd->anchom && x >= 0
		&& (sd->map[y][x] == '1' || sd->map[y][x] == ' '))
		choca = 1;
	return (choca);
}

//Find out which box we are in
//boxx The pos in pixels. pos in which I am between the width of each box
//boxX/Y will be in values ​​of the matrix,u just have to look if it is 0 or 1
int	player_colision(t_scene_data *sd, double x, double y)
{
	int	choca;
	int	casillax;
	int	casillay;

	choca = 0;
	casillax = (int)(x / TILE);
	casillay = (int)(y / TILE);
	if (scene_colision(sd, casillax, casillay))
		choca = 1;
	return (choca);
}
