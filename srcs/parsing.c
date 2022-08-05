#include "fdf.h"

void    ft_freearr(void **arr)
{
    int i;
    
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_build(int fd, t_info *info, int i, int j)
{
	int	*iarr;
	char *s;
	char **arr;

	s = get_next_line(fd);
	if (s)
	{
		ft_build(fd, info, ++i, -1);
		if (!info)
			free(s);
		else
		{
			arr = ft_split(s, ' ');
			iarr = malloc(sizeof(int *) * ft_arrlen(arr));
			if (!iarr)
			{
				ft_freearr((void **)arr);
				return (0);
			}
			while (arr[++j])
			{
				iarr[j] = ft_atoi(arr[j]);
				if ((info->vy - i) *iarr[j] > info->m)
					info->m = iarr[j];
			}
			info->z[i - 1] = iarr;
			info->vx = ft_arrlen(arr);
		}
	}
	else
	{
		info->z = malloc(sizeof(int **) * i);
		info->vy = i;
	}
	return (0);
}

t_info	*ft_parsing(const char *path)
{
	int	fd;
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	info->m = 0;
	fd = open(path, O_RDONLY);
	ft_build(fd, info, 0, -1);
	close(fd);		
	return (info);
}

// t_info	*ft_parsing(const char *path)
// {
// 	int fd;
// 	char **rd;
// 	char *s;
// 	t_info *info;

// 	info = malloc(sizeof(t_info));
// 	if (!info)
// 		return (0);
// 	fd = open(path, O_RDONLY);
// 	s = get_next_line(fd);
// 	info->vx = 0;
// 	info->vy = 0;
// 	while (s)
// 	{
// 		if (info->vx == 0)
// 		{
// 			rd = ft_split(s, ' ');
// 			info->vx = ft_arrlen(rd);
// 			ft_freearr(rd);
// 		}
// 		info->vy++;
// 		free(s);
// 		s= get_next_line(fd);
// 	}
// 	close(fd);
// 	return (info);
// }
