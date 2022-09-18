/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:08:47 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/11 12:08:48 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_map *map)
{
	ft_exit("Cross was clicked, Window has closed\n", map, 0);
	return (0);
}

static int	ft_move(int keycode, t_map *map)
{
	if (keycode == 123 && map->offsetx - (map->lenx / 2.) + 1 <= 0)
		map->offsetx++;
	else if (keycode == 124 && map->offsetx + (map->lenx / 2.) - 1 >= 0)
		map->offsetx--;
	else if (keycode == 125 && map->offsety + (map->leny / 2.) - 1 >= 0)
		map->offsety--;
	else if (keycode == 126 && map->offsety - (map->leny / 2.) + 1 <= 0)
		map->offsety++;
	else if (keycode == 31)
	{
		map->offsetx = 0;
		map->offsety = 0;
	}
	ft_draw(map);
	return (0);
}

static int	ft_rotate(int keycode, t_map *map)
{
	if (keycode == 34 || keycode == 35)
	{
		if (keycode == 34)
			map->is_iso = 1;
		if (keycode == 35)
			map->is_iso = 0;
		map->rx = 0;
		map->ry = 0;
		map->rz = 0;
	}
	else if (keycode == 0)
		map->ry = ((map->ry % 360) + 5);
	else if (keycode == 12)
		map->rx = ((map->rx % 360) + 5);
	else if (keycode == 6)
		map->rz = ((map->rz % 360) + 5);
	ft_draw(map);
	return (0);
}

static int	ft_zoom(int keycode, t_map *map)
{
	if (keycode == 30 && map->scale + 2 < 50)
		map->scale *= 1.5;
	else if (keycode == 33 && map->scale - 2 > 0)
		map->scale /= 1.5;
	else if (keycode == 45 && map->pa < 2)
		map->pa++;
	else if (keycode == 45 && map->pa == 2)
		map->pa = 0;
	ft_draw(map);
	return (0);
}

int	ft_keyhook(int keycode, t_map *map)
{
	if (keycode == 53)
		ft_exit("ESC is pressed, window has closed!\n", map, 1);
	else if (keycode == 0 || keycode == 2 || keycode == 6 || keycode == 8
		|| keycode == 12 || keycode == 14 || keycode == 34 || keycode == 35)
		ft_rotate(keycode, map);
	else if ((keycode >= 123 && keycode <= 126) || keycode == 31)
		ft_move(keycode, map);
	else if (keycode == 30 || keycode == 33 || keycode == 45)
		ft_zoom(keycode, map);
	else if (keycode == 40)
	{
		if (map->inverse == 0)
			map->inverse = 1;
		else
			map->inverse = 0;
		ft_draw(map);
	}
	return (0);
}
