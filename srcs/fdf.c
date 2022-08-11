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
		ace.i++;
	}
}

int	ft_close(int keycode, t_map *map)
{
	int	i;

	i = 0;
	if (keycode == 65307)
	{
		while (i <= map->ht)
			free(map->px[i++]);
		free(map->px);
		mlx_destroy_window(map->mlx, map->mlx_win);
		exit(0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_map map;

	// Check arg
	if (argc != 2)
		return (0);

	// Get input
	ft_getdim(&map, argv[1]);
	printf("Get Dimension [%d][%d]\n", map.wd, map.ht);
	// setup
	ft_setup(&map);
	printf("Setting up variable\n");
	// get altitude
	ft_getalt(&map, argv[1]);
	printf("Get altitude\n");

	map.pa = (float)(map.win_height - 50) / (float)(map.bottom - map.top);
	map.pa = map.size * 1.5;
	map.y = 25 + fabsf((float)map.top * map.pa);
	map.y = 400;
	printf("top [%d] : bottom [%d]\n", map.top, map.bottom);
	printf("size [%f] and pa [%f]\n", map.size, map.pa);
	printf("highest [%d] and lowest [%f]\n", map.highest, 0.0);

	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, map.win_width, map.win_height, "My window");
	map.mlx_img = mlx_new_image(map.mlx, map.win_width, map.win_height);
	map.addr = mlx_get_data_addr(map.mlx_img, &map.bpp, &map.line_size, &map.endian);

	// Draw
	ft_draw(&map);

	// Put
	mlx_put_image_to_window(map.mlx, map.mlx_win, map.mlx_img, 0, 0);

	// Event
	mlx_hook(map.mlx_win, 2, 1L<<0, ft_close, &map);

	// Loop
	mlx_loop(map.mlx);
}
