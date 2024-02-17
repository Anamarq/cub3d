
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
# include "MLX42/include/MLX42/MLX42.h"

#include "cub3d.h"

#define WIDTH 512
#define HEIGHT 512

//static mlx_image_t* image;
//static mlx_t* mlx;

#include <stdio.h>

#define FILAS 10
#define COLUMNAS 10

int nivel1[FILAS][COLUMNAS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct s_scene_data
{
    mlx_image_t* character;
    mlx_t* mlx;
}   t_scene_data;

void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

mlx_image_t	*create_img(mlx_t	*mlx, char *route)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(route);
	if (!texture)
	 	error();
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
	 	error();
	mlx_delete_texture(texture);
	return (img);
}


void ft_draw_map(mlx_t	*mlx)
{
	mlx_image_t	*img = create_img(mlx, "./sprites/wall.png");
	for (int y = 0; y < FILAS; y++) {
		for (int x = 0; x < COLUMNAS; x++) {
			if (nivel1[y][x] == 1)
			{
				if (mlx_image_to_window(mlx, img, x * 50, y * 50) < 0)
					error();
			}
			//printf("PASA, x: %i, y: %i\n", x, y);
		}
	}
}

uint32_t ft_draw_character2D(t_scene_data* scene_data)
{
	//mlx_image_t* image = scene_data->character;
	//mlx_t* mlx = scene_data->mlx;
	if (!(scene_data->character = mlx_new_image(scene_data->mlx, 10, 10)))
	{
		mlx_close_window(scene_data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	for (uint32_t i = 0; i < scene_data->character->width; ++i)
	{
		for (uint32_t y = 0; y < scene_data->character->height; ++y)
		{
			uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
			mlx_put_pixel(scene_data->character, i, y, color);
		}
	}
	if (mlx_image_to_window(scene_data->mlx, scene_data->character, 0, 0) == -1)
	{
		mlx_close_window(scene_data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return 0;
}

void ft_hook(void* param)
{
	//mlx_t* mlx = param;
	//mlx_image_t* image = param;
	t_scene_data* scene_data = param;
	//mlx_t* mlx = scene_data->mlx;

	if (mlx_is_key_down(scene_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(scene_data->mlx);
	if (mlx_is_key_down(scene_data->mlx, MLX_KEY_UP))
		scene_data->character->instances[0].y -= 5;
	if (mlx_is_key_down(scene_data->mlx, MLX_KEY_DOWN))
		scene_data->character->instances[0].y += 5;
	if (mlx_is_key_down(scene_data->mlx, MLX_KEY_LEFT))
		scene_data->character->instances[0].x -= 5;
	if (mlx_is_key_down(scene_data->mlx, MLX_KEY_RIGHT))
		scene_data->character->instances[0].x += 5;
}



// -----------------------------------------------------------------------------
void leaks(void)
{
	system("leaks -q cub3d");
}

/*int32_t main(int32_t argc, const char* argv[])
{
	(void) argc;
	(void) argv;
	atexit(leaks);
	//mlx_t* mlx;
	t_scene_data scene_data;

	//Dibujar mapa (BORRAR)
	for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%d ", nivel1[i][j]);
        }
        printf("\n");
    }

	//Inicializar ventana
	if (!(scene_data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	//DIBUJAR PERSONAJE
	scene_data.character = NULL;
	if(ft_draw_character2D(&scene_data) != 0)
		return(EXIT_FAILURE);
	//DIBUAR MAPA
	ft_draw_map(scene_data.mlx);
	//MOVER PERSONAJE
	mlx_loop_hook(scene_data.mlx, ft_hook, &scene_data);
	mlx_loop(scene_data.mlx);
	mlx_terminate(scene_data.mlx);
	return (EXIT_SUCCESS);
}*/

