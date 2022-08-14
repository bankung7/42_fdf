#ifndef FDF_H
#define FDF_H

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#include <stdio.h>

typedef struct s_px
{
	int z;
	int color;
} t_px;

typedef struct s_line
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	float	dx;
	float	dy;
	float	p;
}	t_line;

typedef struct s_img
{
	void *ptr;
	char *addr;
	int bpp;
	int line_size;
	int endian;
} t_img;

typedef struct s_map
{
	void *mlx;
	void *win;
	t_img img;
	int vw;
	int vh;
	int w_width;
	int	w_height;
	t_px **px;
	float	xo;
	float	yo;
	float	x;
	float	y;
	float	zoom;
} t_map;

// fdf.c
void ft_drawbg(t_map *map, int color);

// draw.c
void ft_put_pixel(t_map *map, int x, int y, int color);
void ft_drawline(t_map *map, float x1, float y1);

// parsing.c
int ft_getdim(t_map *map, char *file);
int ft_getpx(t_map *map, char *file);

// exit.c
int ft_exit(char *str, t_map *map, int n);
int ft_free(void **arr);
int ft_read(t_map *map);

// hook.c
int ft_close(t_map *map);
int ft_keyhook(int keycode, t_map *map);

#endif
