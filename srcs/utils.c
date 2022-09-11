/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:09:14 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/11 12:09:17 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_read(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->vh)
	{
		j = 0;
		while (j < map->vw)
		{
			ft_printf("%d  ", map->px[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	return (0);
}
