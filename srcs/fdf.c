#include "fdf.h"

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
	map.size = 1;
	map.win_width = 600;
	map.pa = 2;
	if (500 / ((map.wd + map.ht) * 2) > 2)
	{
		map.size = 500 / ((map.wd + map.ht) * 2);
		map.win_height = (map.wd + map.ht) * map.size + (map.z[map.yh][map.xh] * map.pa) + 100;
	}
	else
	{
		map.size = 1;
		map.win_width = 2 * map.size * (map.wd + map.ht) + 100;
		map.win_height = (map.wd + map.ht) * map.size + (map.z[map.yh][map.xh] * map.pa) + 100;
	}
	map.x = 50;
	map.y = 50 + (map.wd * map.size) + map.z[map.yh][map.xh] * map.pa;
	ft_printf("%d for %d\n", map.pa, map.hv);
	ft_printf("%d x %d with size %d\n", map.wd, map.ht, map.size);
	ft_printf("%d x %d heighest point %d\n", map.win_width, map.win_height, map.ha);
	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, map.win_width, map.win_height, "My window");
	map.mlx_img = mlx_new_image(map.mlx, map.win_width, map.win_height);
	map.addr = mlx_get_data_addr(map.mlx_img, &map.bpp, &map.line_size, &map.endian);
	ft_draw(&map);
	mlx_put_image_to_window(map.mlx, map.mlx_win, map.mlx_img, 0, 0);
	mlx_loop(map.mlx);
}
