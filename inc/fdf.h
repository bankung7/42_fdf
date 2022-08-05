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

// info data
typedef struct s_info
{
	int	x;
	int y;
	int	vx;
	int	vy;
	int	size;
	int m;
	int	color;
	int **z;
} t_info;

// image structure
typedef struct s_img
{
	void *img;
	char *addr;
	int pixel_bits;
	int line_bytes;
	int endian;
	int width;
	int height;
} t_img;

typedef struct s_data
{
	void *mlx;
	void *win_ptr;
} t_data;

typedef struct s_line
{
	int x0;
	int y0;
	int x1;
	int y1;
	int dx;
	int dy;
	int d;
	int r;
} t_line;

typedef struct s_ace
{
	int i;
	int j;
} t_ace;

// exit.c
void    ft_freearr(void **arr);
void    ft_exit(void **arr1, void *arr2);

// parsing.c
int	ft_arrlen(char **arr);
int	ft_build(int fd, t_info *info, int i, int j);
t_info	*ft_parsing(const char *path);

#endif
