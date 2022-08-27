#include "fdf.h"

int	ft_setup(t_map *map)
{
	map->rx = 45;
	map->ry = 35;
	map->rz = -30;
	map->w_width = 800;
	map->w_height = 800;
	map->lenx = map->vw / 2.;
	map->leny = map->vh / 2.;
	map->x = map->w_width / 2.;
	map->y = map->w_height / 2.;
	if (map->vw > map->vh)
		map->scale = (float)map->w_width / (map->lenx) / 4.;
	else
		map->scale = (float)map->w_height / (map->leny) / 4.;
	map->pa = 1;
	map->inverse = 0;
	return (0);
}

void	ft_menu(t_map *map)
{
	int	color;

	color = 0xffffff;
	if (map->inverse == 1)
		color = ft_inversecolor(color);
	mlx_string_put(map->mlx, map->win, 20, 20, color, "Rx : x");
	mlx_string_put(map->mlx, map->win, 20, 40, color, "Ry : y");
	mlx_string_put(map->mlx, map->win, 20, 60, color, "Rz : z");
	mlx_string_put(map->mlx, map->win, 20, 80, color, "Reset center : c");
	mlx_string_put(map->mlx, map->win, 20, 100, color, "Parallel : p");
	mlx_string_put(map->mlx, map->win, 20, 120, color, "Isometric : i");
	mlx_string_put(map->mlx, map->win, 20, 140, color, "Zoom : [ or ]");
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

int	ft_mixcolor(t_line *line, float pos)
{
	float	dr;
	float	dg;
	float	db;
	t_color	color;

	color.r0 = line->color0 >> 16 & 0xff;
	color.g0 = line->color0 >> 8 & 0xff;
	color.b0 = line->color0 & 0xff;
	color.r1 = line->color1 >> 16 & 0xff;
	color.g1 = line->color1 >> 8 & 0xff;
	color.b1 = line->color1 & 0xff;
	color.step = fmax(fabsf(line->x1 - line->x0), fabsf(line->y1 - line->y0));
	dr = (line->color0 >> 16 & 0xff) + (color.r1 - color.r0) / color.step * pos;
	dg = (line->color0 >> 8 & 0xff) + (color.g1 - color.g0) / color.step * pos;
	db = (line->color0 & 0xff) + (color.b1 - color.b0) / color.step * pos;
	return (((int)dr << 16) + ((int)dg << 8) + db);
}
