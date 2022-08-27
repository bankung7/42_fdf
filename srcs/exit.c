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
	ft_printf("%s", str);
	exit(n);
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
