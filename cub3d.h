/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:56:54 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/06 13:34:31 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
//# include <float.h>
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
	ERROR_NO_COLOR,
	ERROR_MALLOC_ERROR,
	INVALID_CHAR,
	EMPTY_LINE_IN_MAP,
	ERROR_NO_PLAYER,
	ERROR_MANY_PLAYER,
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

//Player data
// x-> position in x
// y-> position in y
//rot_angle->Angle where you look in radians, when looking to the right it is 0
//move_step-> player speed
//rot_step-> the degrees that will rotate when I press
typedef struct s_player_data
{
	double			x;
	double			y;
	double			rot_angle;
	double			move_step;
	double			rot_step;

}					t_player_data;

//Lightning data
// x-> position in x
// y-> position in y
// ray_angle-> Ray angle
//step_angle-> What should be incremented between each ray
//column-> Column where the ray points and will draw the line
//distance-> distance to the wall that the ray hits
//pixel_texturex-> pixel taken from the texture you are going to use, in x
//direction-> direction of the ray on the map, to know which texture to use:
//right 0, left 1, up 2, down 3
//wall_hits-> Point where it collides.
//The collision can be horizontal or vertical
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

//Textures for walls
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
//plane_distance; Distance to plane
//hight_wall; top of the wall
//y0; beginning of the line that draws the wall
//y1; end of the line drawn by the wall
//x; column in which the wall line is drawn
//y0aux; real y0 (it goes off the screen) to calculate the tx pixel and
//y1aux;y1 real (exits the screen) to calculate the pixel tx y
//py; pixel texture and
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

//General data:
//data-> parse data
//character->2D character
//mlx->window
//ply-> player data
//end-> graphic representation of the end of each ray, the collision point
//ray->ray data
//scene-> scene where each line is drawn and seen in 3D
//walls->walls texture
//map-> copy of the parse map
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


void				print_map_content(char **content);
void				print_struct_content(t_data data);
*********************************/

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
int					scene_colision(t_scene_data *sd, int x, int y);
int					player_colision(t_scene_data *sd, double x, double y);

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