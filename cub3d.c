
#include "cub3d.h"

void leaks(void)
{
	system("leaks -q cub3d");
}

void free_memory(t_scene_data* sd)
{
	int i;

	i = 0;
	free(sd->ply);
	free(sd->ray);
	while(i < sd->altom)
	{
		free(sd->map[i]);
		++i;
	}
	free(sd->map);
}

int32_t main(int32_t argc, char* argv[])
{
	t_data	data;

	atexit(leaks); //BORRAR

	t_scene_data sd; //PONER
	parser(argc, argv, &data);
	printf("Aqui\n");
	initialize_data(&sd, data); //PONER
	
	set_graphics(&sd, data); //PONER
	free_memory(&sd); //PONER

	free_struct(&data);


	return (EXIT_SUCCESS);
}