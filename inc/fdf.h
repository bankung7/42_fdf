/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:09:45 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/11 12:09:47 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_color
{
	int		r0;
	int		g0;
	int		b0;
	int		r1;
	int		g1;
	int		b1;
	float	step;
}	t_color;

typedef struct s_px
{
	int	z;
	int	color;
}	t_px;

typedef struct s_line
{
	int		color0;
	int		color1;
	float	x;
	float	y;
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	float	z0;
	float	z1;
	float	dx;
	float	dy;
	float	p;
}	t_line;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_ace
{
	int	i;
	int	j;
}	t_ace;

typedef struct s_map
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		vw;
	int		vh;
	int		w_width;
	int		w_height;
	int		rx;
	int		ry;
	int		rz;
	t_px	**px;
	int		pa;
	float	scale;
	int		offsetx;
	int		offsety;
	float	lenx;
	float	leny;
	int		inverse;
	int		is_iso;
}	t_map;

// fdf.c
int		ft_draw(t_map *map);

// draw.c
void	ft_put_pixel(t_map *map, int x, int y, int color);
void	ft_drawline(t_map *map, t_ace *ace, float x1, float y1);

// parsing.c
int		ft_getdim(t_map *map, char *file);
int		ft_getpx(t_map *map, char *file);

// exit.c
int		ft_free(void **arr);
int		ft_exit(char *str, t_map *map, int n);

// hook.c
int		ft_close(t_map *map);
int		ft_keyhook(int keycode, t_map *map);

// matrix.c
void	ft_2d(t_map *map, t_line *line);

// setup.c
int		ft_setup(t_map *map);
void	ft_drawbg(t_map *map, int color);
void	ft_menu(t_map *map);

// utils.c
int		ft_checkedge(t_map *map, t_line *line, float x, float y);
int		ft_mixcolor(t_line *line, float pos);
int		ft_inversecolor(int color);
int		ft_read(t_map *map);

#endif
