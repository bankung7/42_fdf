#include "fdf.h"

void ft_put_pixel(t_map *map, int x, int y, int color)
{
	char *ptr;

	ptr = map->addr + (y * map->line_size + x * (map->bpp / 8));
	*(unsigned int *)ptr = color;
}

void ft_plotlow(t_map *map, t_line *line, int color)
{
	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
	if (line->dy < 0)
	{
		line->r = 1;
		line->dy *= -1;
	}
	line->d = (2 * line->dy) - line->dx;
	while (line->x0 <= line->x1)
	{
		ft_put_pixel(map, line->x0, line->y0, color);
		line->x0++;
		if (line->d > 0)
		{
			if (line->r == 1)
				line->y0--;
			else
				line->y0++;
			line->d += (2 * (line->dy - line->dx));
		}
		else
			line->d += (2 * line->dy);
	}
}

void ft_plothigh(t_map *map, t_line *line, int color)
{
	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
	if (line->dx < 0)
	{
		line->r = 1;
		line->dx *= -1;
	}
	line->d = (2 * line->dx) - line->dy;
	while (line->y0 <= line->y1)
	{
		ft_put_pixel(map, line->x0, line->y0, color);
		line->y0++;
		if (line->d >= 0)
		{
			if (line->r == 1)
				line->x0--;
			else
				line->x0++;
			line->d += 2 * (line->dx - line->dy);
		}
		else
			line->d += 2 * line->dx;
	}
}

void ft_setline(t_map *map, t_ace ace, t_line *line, int r)
{
	int z;

	if (r == -1)
		z = map->z[ace.i][ace.j + 1] * map->pa;
	else
		z = map->z[ace.i + 1][ace.j] * map->pa;
	line->x0 = map->x + (2 * map->size * ace.i) + (2 * map->size * ace.j);
	line->y0 = map->y + (map->size * ace.i) - (map->size * ace.j) - (map->z[ace.i][ace.j] * map->pa);
	line->x1 = map->x + (2 * map->size * (ace.i + 1)) + (2 * map->size * ace.j);
	line->y1 = map->y + (map->size * ace.i) - (map->size * ace.j) + (r * map->size) - z;
	line->d = 0;
	line->r = 0;
}

void	ft_swapvalue(t_line *line)
{
	int	a;

	a = line->x0;
	line->x0 = line->x1;
	line->x1 = a;
	a = line->y0;
	line->y0 = line->y1;
	line->y1 = a;
}

void ft_plotline(t_map *map, t_ace ace, int r, int color)
{
	t_line line;

	ft_setline(map, ace, &line, r);
	if (abs(line.y1 - line.y0) < abs(line.x1 - line.x0))
	{
		if (line.x0 > line.x1)
		{
			ft_swapvalue(&line);
			ft_plotlow(map, &line, color);
		}
		else
			ft_plotlow(map, &line, color);
	}
	else
	{
		if (line.y0 > line.y1)
		{
			ft_swapvalue(&line);
			ft_plothigh(map, &line, color);
		}
		else
			ft_plothigh(map, &line, color);
	}
}
