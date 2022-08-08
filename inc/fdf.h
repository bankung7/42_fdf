#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_ace
{
	int	i;
	int	j;
}	t_ace;

typedef struct	s_line
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	float	dx;
	float	dy;
	float	d;
	float	r;
}	t_line;

typedef struct	s_map
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	int win_width;
	int	win_height;
	int	wd;
	int	ht;
	int	**z;
	char	*addr;
	int	bpp;
	int	line_size;
	int	endian;
	float	size;
	float	x;
	float	y;
	int ha;
	int	xh;
	int	yh;
	int la;
	int xl;
	int yl;
	float	pa;
}	t_map;

// parsing.c
void	ft_parsing(t_map *map, char *file);

// draw.c
void	ft_put_pixel(t_map *map, int x, int y, int color);
void	ft_plotline(t_map *map, t_ace ace, int r, int color);

#endif
