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
			// printf("[%d][%d]\n", ace.i, ace.j);
			if (ace.i != map->ht - 1)
				ft_plotline(map, ace, 1, 0xFFFFFF);
			if (ace.j < map->wd - 1)
				ft_plotline(map, ace, -1, 0xFFFFFF);
			ace.j++;
		}
		ace.i++;
	}
}

int main(int argc, char **argv)
{
	t_map map;

	if (argc != 2)
		return (0);
	ft_parsing(&map, argv[1]);
	map.win_width = 600;
	map.win_height = 600;
	map.pa = 2;
	// map.size = 1;
	map.size = ((float)(map.win_width - 50) / (map.wd + map.ht) / 2);
	if (map.size < 0.65)
	{
		map.size = 0.65;
		map.win_width = map.size * (map.wd + map.ht) * 2 + 50;
	}
	printf("%d %d [%f]\n", map.win_width, (map.wd + map.ht), map.size);
	map.pa = (float)(map.win_height - 50) / abs(map.ha - map.la);
	if (map.pa < 0.65)
	{
		map.pa = 0.65;
		map.win_height = 50 + abs(map.ha - map.la) * map.pa;
	}
	printf("ha: %d, la: %d, pa: %f\n", map.ha, map.la, map.pa);
	map.x = 25;
	map.y = 600;
	printf("%d %d %d\n", map.xh, map.yh, map.z[map.yh][map.xh]);
	printf("%d, %d\n", map.win_width, map.win_height);
	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, map.win_width, map.win_height, "My window");
	map.mlx_img = mlx_new_image(map.mlx, map.win_width, map.win_height);
	map.addr = mlx_get_data_addr(map.mlx_img, &map.bpp, &map.line_size, &map.endian);
	ft_draw(&map);
	mlx_put_image_to_window(map.mlx, map.mlx_win, map.mlx_img, 0, 0);
	mlx_loop(map.mlx);
}
