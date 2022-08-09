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

typedef struct s_ace
{
	int i;
	int j;
} t_ace;

typedef struct s_line
{
	float x0;
	float y0;
	float x1;
	float y1;
	float dx;
	float dy;
	float d;
	float r;
} t_line;

typedef struct s_map
{
	void *mlx;
	void *mlx_win;
	void *mlx_img;
	char *addr;
	int bpp;
	int line_size;
	int endian;
	int win_width;
	int win_height;
	int wd;
	int ht;
	int **alt;
	int	**color;
	float size;
	float pa;
	int top;
	int bottom;
	int	highest;
	float	x;
	float	y;
} t_map;

// parsing.c
void ft_getdim(t_map *map, char *file);
void ft_getalt(t_map *map, char *file);

// setup.c
void ft_setup(t_map *map);

// draw.c
void ft_put_pixel(t_map *map, int x, int y, int color);
void ft_plotline(t_map *map, t_ace ace, int r, int color);

#endif
