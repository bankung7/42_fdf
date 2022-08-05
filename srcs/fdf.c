#include "fdf.h"

void	ft_draw(t_map *map)
{
	ft_put_pixel(map, 200, 200, 0xFF0000);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (0);
	ft_parsing(&map, argv[1]);
	ft_printf("%d x %d\n", map.wd, map.ht);

	map.size = 2;
	map.mlx = mlx_init();
	map.mlx_win = mlx_new_window(map.mlx, 600, 600, "My window");
	map.mlx_img = mlx_new_image(map.mlx, 0, 0);
	map.addr = mlx_get_data_addr(map.mlx_img, &map.bpp, &map.line_size, &map.endian);
	ft_draw(&map);
	mlx_put_image_to_window(map.mlx, map.mlx_win, map.mlx_img, 0, 0);
	mlx_loop(map.mlx);
	
}
