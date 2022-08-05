#include "fdf.h"

int	ft_getwidth(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = 0;
	return (i);
}

void	ft_setz(t_map *map, char *line, int i)
{
	int	j;
	char	**arr;

	map->z[i] = malloc(sizeof(int) * map->wd);
	if (map->z[i] == 0)
	{
		ft_getwidth((void**)map->z[i]);
		exit(0);
	}
	arr = ft_split(line, ' ');
	free(line);
	j = 0;
	while (arr[j])
	{
		map->z[i][j] = ft_atoi(arr[j]);
		j++;
	}
	
}

void	ft_getz(t_map *map, char *file)
{
	int	fd;
	int	i;
	char	*line;

	fd = open(file, O_RDONLY);
	i = 0;
	map->z = malloc(sizeof(int*) * map->ht);
	if (map->z == 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		ft_setz(map, line, i++);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_getdim(t_map *map, char *file)
{
	int	fd;
	char	*line;
	char	**arr;

	map->ht = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	arr = ft_split(line, ' ');
	map->wd = ft_getwidth((void**)arr);
	while (line != 0)
	{
		map->ht++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	ft_parsing(t_map *map, char *file)
{
	ft_getdim(map, file);
	ft_getz(map, file);
}
