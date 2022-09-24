/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:08:40 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/11 12:08:41 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_draw(t_map *map)
{
	t_ace	ace;

	ace.i = 0;
	ft_drawbg(map, 0x0);
	while (ace.i < map->vh)
	{
		ace.j = 0;
		while (ace.j < map->vw)
		{
			if (ace.i < map->vh - 1)
				ft_drawline(map, &ace, ace.j, ace.i + 1);
			if (ace.j < map->vw - 1)
				ft_drawline(map, &ace, ace.j + 1, ace.i);
			ace.j++;
		}
		ace.i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img.ptr, 0, 0);
	ft_menu(map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		ft_exit("Incorrect format : ./fdf [file.fdf]\n", 0, 2);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_exit("Something went wrong, try again later\n", 0, 2);
	ft_memset(map, 0, sizeof(t_map));
	ft_getdim(map, argv[1]);
	ft_getpx(map, argv[1]);
	ft_setup(map);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->w_width, map->w_height, "My fdf");
	map->img.ptr = mlx_new_image(map->mlx, map->w_width, map->w_height);
	map->img.addr = mlx_get_data_addr(map->img.ptr,
			&map->img.bpp, &map->img.line_size, &map->img.endian);
	mlx_loop_hook(map->mlx, ft_draw, map);
	mlx_hook(map->win, 2, 1L << 0, ft_keyhook, map);
	mlx_hook(map->win, 17, 0, ft_close, map);
	mlx_loop(map->mlx);
	return (0);
}
