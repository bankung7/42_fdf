/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:08:25 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/11 12:08:27 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pixel(t_map *map, int x, int y, int color)
{
	char	*ptr;

	if (x < 0 || x >= map->w_width || y < 0 || y >= map->w_height)
		return ;
	ptr = map->img.addr + (y * map->img.line_size) + (x * (map->img.bpp / 8));
	if (map->inverse == 1)
		color = ft_inversecolor(color);
	*(unsigned int *)ptr = color;
}

static void	ft_linehigh(t_map *map, t_line *line)
{
	float	xi;

	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
	xi = 1;
	line->y = line->y0;
	if (line->dx < 0)
	{
		xi = -1;
		line->dx = -line->dx;
	}
	line->p = (2.0 * line->dx) - line->dy;
	while (line->y < line->y1)
	{
		ft_checkedge(map, line, line->x0, line->y);
		if (line->p > 0)
		{
			line->x0 += xi;
			line->p += (2.0 * (line->dx - line->dy));
		}
		else
			line->p += 2.0 * line->dx;
		line->y++;
	}
}

static void	ft_linelow(t_map *map, t_line *line)
{
	float	yi;

	line->dx = line->x1 - line->x0;
	line->dy = line->y1 - line->y0;
	yi = 1;
	line->x = line->x0;
	if (line->dy < 0)
	{
		yi = -1;
		line->dy = -line->dy;
	}
	line->p = (2.0 * line->dy) - line->dx;
	while (line->x < line->x1)
	{
		ft_checkedge(map, line, line->x, line->y0);
		if (line->p > 0)
		{
			line->y0 += yi;
			line->p += (2.0 * (line->dy - line->dx));
		}
		else
			line->p += 2.0 * line->dy;
		line->x++;
	}
}

static void	ft_swap(t_line *line, void (*f)(t_map *, t_line *), t_map *map)
{
	int	x;

	x = line->x0;
	line->x0 = line->x1;
	line->x1 = x;
	x = line->y0;
	line->y0 = line->y1;
	line->y1 = x;
	x = line->color0;
	line->color0 = line->color1;
	line->color1 = x;
	f(map, line);
}

void	ft_drawline(t_map *map, t_ace *ace, float x1, float y1)
{
	t_line	line;

	line.x0 = ace->j - (map->vw / 2.);
	line.y0 = ace->i - (map->vh / 2.);
	line.z0 = map->px[ace->i][ace->j].z * map->pa;
	line.color0 = map->px[ace->i][ace->j].color;
	line.x1 = x1 - (map->vw / 2.);
	line.y1 = y1 - (map->vh / 2.);
	line.z1 = map->px[(int)y1][(int)x1].z * map->pa;
	line.color1 = map->px[(int)y1][(int)x1].color;
	ft_2d(map, &line);
	if (fabsf(line.y1 - line.y0) < fabsf(line.x1 - line.x0))
	{
		if (line.x0 > line.x1)
			ft_swap(&line, ft_linelow, map);
		else
			ft_linelow(map, &line);
	}
	else
	{
		if (line.y0 > line.y1)
			ft_swap(&line, ft_linehigh, map);
		else
			ft_linehigh(map, &line);
	}
}
