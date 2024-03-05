/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:56:54 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/05 17:28:36 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 1000
# define TILE 1000
# define FOV 60

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_FILE_TYPE,
	ERROR_FILE,
	ERROR_FILE_EMPTY,
	INVALID_CHAR_IN_LINES,
	ERROR_NO_PATHS,
	ERROR_MALLOC_ERROR,
	INVALID_CHAR,
	EMPTY_LINE_IN_MAP,
	END = 99,
}					t_error;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_data
{
	int				fd;
	t_error			error;
	char			*pipeline;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	t_color			floor;
	t_color			ceiling;
	char			**map;
	int				x;
	int				y;
}					t_data;

typedef struct s_player_data
{
	double			x;
	double			y;
	double			rot_angle;
	double			move_step;
	double			rot_step;

}					t_player_data;

typedef struct s_ray_data
{
	double			x;
	double			y;
	double			ray_angle;
	double			step_angle;
	int				columna;
	double			distance;
	int				pixel_texturex;
	int				direction;
	int				wall_hit_x;
	int				wall_hit_y;
	int				wall_hit_x_horiz;
	int				wall_hit_y_horiz;
	int				wall_hit_x_vert;
	int				wall_hit_y_vert;
}					t_ray_data;

typedef struct s_walls
{
	mlx_image_t		*tx_right;
	mlx_image_t		*tx_left;
	mlx_image_t		*tx_up;
	mlx_image_t		*tx_down;
}					t_walls;

//Casting2
typedef struct s_colision_data
{
	double			x_intercept;
	double			y_intercept;
	int				x_step;
	int				y_step;
}					t_colision_data;

//render.c
typedef struct s_render_data
{
	double			plane_distance;
	double			hight_wall;
	int				y0;
	int				y1;
	int				x;
	int				y0aux;
	int				y1aux;
	int				py;
}					t_render_data;

typedef struct s_scene_data
{
	int				altom;
	int				anchom;
	mlx_image_t		*character;
	mlx_t			*mlx;
	t_player_data	*ply;
	mlx_image_t		*end;
	t_ray_data		*ray;
	mlx_image_t		*scene;
	t_walls			walls;
	char			**map;
}					t_scene_data;

/***********************************
 ****** PARSER FUNCTIONS ***********
***********************************/

void				init_data_struct(t_data *data);
int					check_params(int argc, char **argv, t_data *data);
void				ft_error(t_data data);
void				ft_error_file_content(t_data *data);
char				**get_file_input(t_data *data);
char				*ft_join_free(char *s1, char *s2);
int					ft_array_len(char **str);
int					is_invalid_char_in_map(char *line, size_t n);
int					is_all_spaces(char *line);
int					is_line_correct(t_data *data, char *line);
int					is_color_line(char *line);
int					is_color_format(char *line, int type, t_data *data);
int					is_path_format(char *line, int type, t_data *data);
int					is_path_line(char *line);
void				free_struct(t_data *data);
int					is_map_start(char *line, t_data data);
int					is_map_line_correct(char *line, t_data *data);
t_point				find_person(char **map, t_point size);
void				flood_fill(char **tab, t_point size, t_point begin);
t_point				get_size(char **map, int len);
char				**copy_map(char **map, t_point size);
char				**copy_and_encase_map(char **map, t_point size);
t_point				find_first_zero(char **map, t_point size);
int					is_map_different(char **copy, char **map, t_point size);
int					is_map_correct(t_data *data, t_point size);
int					is_file_empty(char *line, t_data *data);
int					parser(int argc, char **argv, t_data *data);

/**********************************
 ******* DEBUG PARSER FUNCTIONS ***
*********************************/

void				print_map_content(char **content);
void				print_struct_content(t_data data);

//Graphics part
//Draw
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void				create_walls(t_scene_data *sd, t_data data);
void				draw_background(t_color skc, t_color fc, mlx_t *mlx);
void				draw_3d(t_scene_data *scene_data);
void				draw_map2d(t_scene_data *sd);
void				draw_character2d(t_scene_data *sd);
void				draw_end(t_scene_data *scene_data);

//utils
void				error(mlx_t *mlx);
double				degrees_to_radians(double angle);
double				normalize_angle(double angle);
double				distance_between_points(double x1, double y1, double x2,
						double y2);

//colisions & ray casting
int					scene_colision(char **matriz, int x, int y);
int					player_colision(char **matrix, double x, double y);

int					horizontal_colision(int down, int left, t_ray_data *ray,
						t_scene_data *sd);
int					vertical_colision(int down, int left, t_ray_data *ray,
						t_scene_data *sd);
void				cast(t_ray_data *ray, t_scene_data *sd);
//render
void				calculate_ray(t_scene_data *sd);
//loop
void				ft_hook(void *param);
//initialize
void				initialize_data(t_scene_data *scene_data,
						t_data parse_data);
//void set_player(t_scene_data* sd);
void				set_graphics(t_scene_data *sd, t_data data);

#endif