#include "fdf.h"
#include <stdio.h>

void ft_draw(t_map *map)
{
	t_ace ace;

	ace.i = 0;

	while (ace.i < map->ht)
	{
		ace.j = 0;
		while (ace.j < map->wd)
		{
			if (ace.i != map->ht - 1)
				ft_plotline(map, ace, 1, map->px[ace.i][ace.j].color);
			if (ace.j < map->wd - 1)
				ft_plotline(map, ace, -1, map->px[ace.i][ace.j].color);
			ace.j++;
		}
		mlx_put_image_to_window(map->mlx, map->mlx_win, map->mlx_img, 0, 0);
		ace.i++;
	}
}

int main(int argc, char **argv)
{
	t_map *map;

	// Check arg
	if (argc != 2)
		return (0);

	map = malloc(sizeof(t_map));
	// Get input
	ft_getdim(map, argv[1]);
	printf("Get Dimension [%d][%d]\n", map->wd, map->ht);
	// setup
	ft_setup(map);
	printf("Setting up variable\n");
	// get altitude
	ft_getalt(map, argv[1]);
	printf("Get altitude\n");

	// map->pa = (float)(map->win_height - 50) / (float)(map->bottom - map->top);
	// map->pa = map->size * 1.5;
	// map->size = 10;
	printf("top [%d] : bottom [%d]\n", map->top, map->bottom);
	printf("size [%f] and pa [%f]\n", map->size, map->pa);
	printf("highest [%d] and lowest [%f]\n", map->highest, 0.0);

	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, map->win_width, map->win_height, "My window");
	map->mlx_img = mlx_new_image(map->mlx, map->win_width, map->win_height);
	map->addr = mlx_get_data_addr(map->mlx_img, &map->bpp, &map->line_size, &map->endian);
	
	ft_drawbg(map);

	map->size = 20;
	// Draw and put
	ft_draw(map);

	// Event close
	mlx_hook(map->mlx_win, 2, 1L << 0, ft_keyhook, map);

	// Loop
	mlx_loop(map->mlx);
}
