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
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	d;
	int	r;
}	t_line;

typedef struct	s_map
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	int	wd;
	int	ht;
	int	**z;
	char	*addr;
	int	bpp;
	int	line_size;
	int	endian;
	int	size;
}	t_map;

// parsing.c
void	ft_parsing(t_map *map, char *file);

// draw.c
void	ft_put_pixel(t_map *map, int x, int y, int color);
void	ft_plotline(t_map *map, t_ace ace, int r);

#endif
