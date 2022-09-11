/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:09:08 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/11 12:09:10 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_setup(t_map *map)
{
	float	v;

	v = 3.1416 / 180.;
	map->rx = 0;
	map->ry = 0;
	map->rz = 0;
	map->w_width = 800;
	map->w_height = 800;
	map->lenx = (map->vw * cos(45 * v)) + (map->vh * sin(45 * v));
	map->leny = (map->vw * sin(45 * v)) + (map->vh * cos(45 * v));
	map->offsetx = 0;
	map->offsety = 0;
	if (map->vw > map->vh)
		map->scale = (float)map->w_width / (map->lenx) / 2.;
	else
		map->scale = (float)map->w_height / (map->leny) / 2.;
	map->pa = 1;
	map->inverse = 0;
	map->is_iso = 1;
	return (0);
}

void	ft_menu(t_map *map)
{
	int	color;

	color = 0xffffff;
	if (map->inverse == 1)
		color = ft_inversecolor(color);
	mlx_string_put(map->mlx, map->win, 20, 20, color, "Rx : q");
	mlx_string_put(map->mlx, map->win, 20, 40, color, "Ry : a");
	mlx_string_put(map->mlx, map->win, 20, 60, color, "Rz : z");
	mlx_string_put(map->mlx, map->win, 20, 80, color, "Centering : c");
	mlx_string_put(map->mlx, map->win, 20, 100, color, "Parallel : p");
	mlx_string_put(map->mlx, map->win, 20, 120, color, "Isometric : i");
	mlx_string_put(map->mlx, map->win, 20, 140, color, "Zoom : [ or ]");
	mlx_string_put(map->mlx, map->win, 20, 160, color, "Altitude : n");
	mlx_string_put(map->mlx, map->win, 20, 180, color, "Inverse Color : k");
}

void	ft_drawbg(t_map *map, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->w_height)
	{
		j = 0;
		while (j < map->w_width)
			ft_put_pixel(map, i, j++, color);
		i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img.ptr, 0, 0);
}
