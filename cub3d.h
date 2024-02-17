/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:56:54 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/17 16:04:44 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_FILE,
	ERROR_NO_PATHS,
	ERROR_MALLOC_ERROR,
	END = 99,
}	t_error;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_data
{
	t_error				error;
	char				*pipeline;
	char				*no;
	char				*so;
    char				*we;
	char				*ea;
    t_color             floor;
    t_color             ceiling;
}						t_data;

#endif