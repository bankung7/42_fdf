#include "fdf.h"
#include <stdio.h>

int ft_getwidth(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = 0;
	return (i);
}

void ft_setz(t_map *map, char *line, int i)
{
	int j;
	char **arr;

	map->z[i] = malloc(sizeof(int) * map->wd + 1);
	if (map->z[i] == 0)
	{
		ft_getwidth((void **)map->z);
		exit(0);
	}
	arr = ft_split(line, ' ');
	free(line);
	j = -1;
	while (arr[++j])
	{
		map->z[i][j] = ft_atoi(arr[j]);
		if ((i - j) - (map->z[i][j]) < map->ha)
		{
			map->xh = j;
			map->yh = i;
			map->ha = (i - j) - (map->z[i][j]);
		}
		else if ((i - j) - (map->z[i][j]) > map->la)
		{
			map->xl = j;
			map->yl = i;
			map->la = (i - j) - (map->z[i][j]);
		}
	}
	map->z[i][++j] = 0;
}

void ft_getz(t_map *map, char *file)
{
	int fd;
	int i;
	int j;
	char *line;

	fd = open(file, O_RDONLY);
	i = 0;
	map->z = malloc(sizeof(int *) * map->ht + 1);
	if (map->z == 0)
		return;
	line = get_next_line(fd);
	while (line)
	{
		ft_setz(map, line, i++);
		line = get_next_line(fd);
	}
	j = 0;
	map->z[i] = malloc(sizeof(int) * map->wd + 1);
	if (!map->z[i])
	{
		ft_getwidth((void **)map->z);
		exit(0);
	}
	while (j <= map->wd)
		map->z[i][j++] = 0;
	close(fd);
}

void ft_getdim(t_map *map, char *file)
{
	int fd;
	char *line;
	char **arr;

	map->ht = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	arr = ft_split(line, ' ');
	map->wd = ft_getwidth((void **)arr);
	while (line != 0)
	{
		map->ht++;
		free(line);
		line = get_next_line(fd);
	}
	printf("height: %d\n", map->ht);
	close(fd);
}

void ft_parsing(t_map *map, char *file)
{
	map->ha = 0;
	map->la = 0;
	ft_getdim(map, file);
	ft_getz(map, file);
}
