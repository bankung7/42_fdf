#include "fdf.h"
#include <stdio.h>

int	ft_close(t_map *map)
{
	ft_exit("Closing window\n", map, 0);
	return (0);
}

int	ft_move(int keycode, t_map *map)
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

int	ft_rotate(int keycode, t_map *map)
{
	if (keycode == 34)
	{
		map->rx = 45;
		map->ry = 35;
		map->rz = 330;
	}
	else if (keycode == 35)
	{
		map->rx = 0;
		map->ry = 0;
		map->rz = 0;
	}
	else if (keycode == 0)
		map->ry = (((int)map->ry % 360) + 5);
	else if (keycode == 12)
		map->rx = (((int)map->rx % 360) + 5);
	else if (keycode == 6)
		map->rz = (((int)map->rz % 360) + 5);
	printf("[%.2f][%.2f][%.2f]\n", map->rx, map->ry, map->rz);
	ft_draw(map);
	return (0);
}

int	ft_zoom(int keycode, t_map *map)
{
	if (keycode == 30 && map->scale + 2 < 50)
		map->scale += 2;
	else if (keycode == 33 && map->scale - 2 > 0)
		map->scale -= 2;
	ft_draw(map);
	return (0);
}

int	ft_keyhook(int keycode, t_map *map)
{
	if (keycode == 53)
		ft_close(map);
	else if (keycode == 0 || keycode == 2 || keycode == 6 || keycode == 8
		|| keycode == 12 || keycode == 14 || keycode == 34 || keycode == 35)
		ft_rotate(keycode, map);
	else if ((keycode >= 123 && keycode <= 126) || keycode == 31)
		ft_move(keycode, map);
	else if (keycode == 30 || keycode == 33)
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
