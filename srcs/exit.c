#include "fdf.h"

int	ft_free(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

int	ft_exit(char *str, t_map *map, int n)
{
	int	i;

	i = 0;
	if (map && map->px)
	{
		while (i < map->vh)
			free(map->px[i++]);
		free(map->px);
	}
	ft_putstr_fd(str, n);
	exit(n);
}
