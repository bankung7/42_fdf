#include "fdf.h"

void	ft_put_pixel(t_map *map, int x, int y, int color)
{
	char	*ptr;

	ptr = map->addr + (y * map->line_size + x * (map->bpp / 8));
	*(unsigned int*)ptr = color;
}

void	ft_plotlow(t_map *map, t_line line)
{
	line.dx = line.x1 - line.x0;
	line.dy = line.y1 - line.y0;
	if (line.dy < 0)
	{
		line.r = 1;
		line.dy *= -1;
	}
	line.d = (2 * line.dy) - line.dx;
	while (line.x0 <= line.x1)
	{
		ft_put_pixel(map, line.x0, line.y0, 0xFFFFFF);
		line.x0++;
		if (line.d > 0)
		{
			if (line.r == 1)
				line.y0--;
			else
				line.y0++;
			line.d += (2 * (line.dy - line.dx));
		}
		else
			line.d += (2 * line.dy);
		ft_printf("here %d %d\n", line.x0, line.y0);
	}
}

void	ft_plothigh(t_map *map, t_line line)
{
	line.dx = line.x1 - line.x0;
	line.dy = line.y1 - line.y0;
	if (line.dx < 0)
	{
		line.r = 1;
		line.dx *= -1;
	}
	line.d = (2 * line.dx) - line.dy;
	while (line.y0 <= line.y1)
	{
		ft_put_pixel(map, line.x0, line.y0, 0xFFFFFF);
		line.y0++;
		if (line.d >= 0)
		{
			if (line.r == 1)
				line.x0--;
			else
				line.x0++;
			line.d += 2 * (line.dx - line.dy);
		}
		else
			line.d += 2 * line.dx;
	}
}

void	ft_plotline(t_map *map, t_ace ace, int r)
{
	int	x;
	int	y;
	t_line	line;

	x = 0;
	y = 0;
	line.x0 = x + (2 * map->size * ace.i) + (2 * map->size * ace.j);
	line.y0 = y + (map->size * ace.i) - (map->size * ace.j);
	line.x1 = x + (2 * map->size * (ace.i + 1)) + (2 * map->size * ace.j);
	line.y1 = y + (map->size * ace.i) - (map->size * ace.j) + (r * map->size);
	if (abs(line.y1 - line.y0) < abs(line.x1 - line.x0))
	{
		if (line.x0 > line.x1)
			ft_plotlow(map, (t_line){line.x1, line.y1, line.x0, line.y0, 0, 0, 0, 0});
		else
			ft_plotlow(map, (t_line){line.x0, line.y0, line.x1, line.y1, 0, 0, 0, 0});

	}
	else
	{
		if (line.y0 > line.y1)
			ft_plothigh(map, (t_line){line.x1, line.y1, line.x0, line.y0, 0, 0, 0, 0});
		else
			ft_plothigh(map, (t_line){line.x0, line.y0, line.x1, line.y1, 0, 0, 0, 0});
	}
}
