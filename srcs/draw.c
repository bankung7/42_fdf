#include "fdf.h"

void ft_put_pixel(t_map *map, int x, int y, int color)
{
	char *ptr;

	if ((x >= 0 && x <= map->win_width) && (y >= 0 && y <= map->win_height))
	{
		ptr = map->addr + (y * map->line_size + x * (map->bpp / 8));
		*(unsigned int *)ptr = color;
	}
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
	line->d = (2.0 * line->dy) - line->dx;
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
			line->d += (2.0 * (line->dy - line->dx));
		}
		else
			line->d += (2.0 * line->dy);
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
	line->d = (2.0 * line->dx) - line->dy;
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
			line->d += 2.0 * (line->dx - line->dy);
		}
		else
			line->d += 2.0 * line->dx;
	}
}

void ft_setline(t_map *map, t_ace ace, t_line *line, int r)
{
	float z;

	if (r == -1)
		z = map->px[ace.i][ace.j + 1].alt * map->pa;
	else
		z = map->px[ace.i + 1][ace.j].alt * map->pa;
	line->x0 = map->x + (2.0 * map->size * ace.i) + (2.0 * map->size * ace.j);
	line->y0 = map->y + (map->size * ace.i) - (map->size * ace.j) - (map->px[ace.i][ace.j].alt * map->pa);
	line->x1 = map->x + (2.0 * map->size * (ace.i + 1)) + (2.0 * map->size * ace.j);
	line->y1 = map->y + (map->size * ace.i) - (map->size * ace.j) + (r * map->size) - z;
	line->d = 0;
	line->r = 0;
}

void	ft_swapvalue(t_line *line)
{
	float	a;

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
	if (fabsf(line.y1 - line.y0) < fabsf(line.x1 - line.x0))
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
