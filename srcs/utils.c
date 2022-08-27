#include "fdf.h"

int	ft_checkedge(t_map *map, t_line *line, float x, float y)
{
	float	pos;

	if (fabsf(line->y1 - line->y0) > fabsf(line->x1 - line->x0))
		pos = fabsf(line->y - line->y0);
	else
		pos = fabsf(line->x - line->x0);
	ft_put_pixel(map, x, y, ft_mixcolor(line, pos));
	return (0);
}

int	ft_inversecolor(int color)
{
	int	ir;
	int	ig;
	int	ib;

	ir = color >> 16 & 0xff;
	ig = color >> 8 & 0xff;
	ib = color & 0xff;
	ir = (255 - ir);
	ig = (255 - ig);
	ib = (255 - ib);
	return ((ir << 16) + (ig << 8) + ib);
}
