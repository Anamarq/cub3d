/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:56:54 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/23 18:46:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_FILE,
    ERROR_FILE_EMPTY,
	ERROR_NO_PATHS,
	ERROR_MALLOC_ERROR,
	INVALID_CHAR,
	END = 99,
}	t_error;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct	s_point
{
	
	int			x;
	int			y;
}				t_point;
typedef struct s_data
{
    int                 fd;
	t_error				error;
	char				*pipeline;
	char				*no;
	char				*so;
    char				*we;
	char				*ea;
    t_color             floor;
    t_color             ceiling;
	char**				map;
}						t_data;

#endif


/***********************************
 ****** PARSER FUNCTIONS ***********
***********************************/

void init_data_struct(t_data *data);
int check_params(int argc, char **argv, t_data *data);
void ft_error(t_data data);
char **get_file_input(t_data *data);
char	*ft_join_free(char *s1, char *s2);
int	ft_array_len(char **str);
int is_invalid_char_in_map(char *line, size_t n);
int is_all_spaces(char *line);
int is_line_correct(t_data *data, char *line);
int is_color_line(char *line);
int is_color_format(char *line, int type, t_data *data);
int is_path_format(char *line, int type, t_data *data);
int is_path_line(char *line);
void free_struct(t_data *data);
int is_map_start(char *line, t_data data);
int is_map_line_correct(char *line, t_data *data);
t_point find_person(char **map, t_point size);
void	flood_fill(char **tab, t_point size, t_point begin);
t_point get_size(char **map);
char **copy_map(char **map, t_point size);
char **copy_and_encase_map(char **map, t_point size);
t_point find_first_zero(char **map, t_point size);
int is_map_different(char **copy, char **map, t_point size);
int is_map_correct(t_data *data, t_point size);

/**********************************
 ******* DEBUG PARSER FUNCTIONS ***
*********************************/

void print_map_content(char **content);
void print_struct_content(t_data data);