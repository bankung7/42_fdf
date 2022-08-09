#include "fdf.h"
#include <stdio.h>

void ft_free(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void ft_trackht(t_map *map, int i, int j)
{
	int value;
	// char **attr;

	value = (i - j) * map->size - map->alt[i][j] * map->pa;
	if (value < map->top)
		map->top = value;
	if (value > map->bottom)
		map->bottom = value;
	if (map->alt[i][j] > map->highest)
		map->highest = map->alt[i][j];
	// if (ft_strchr(a, ',') >= 0)
	// {
	// 	attr = ft_split(a, ',');
	// 	printf("%d\n", ft_atoi(attr[1]));
	// 	map->color[i][j] = ft_atoi(attr[1]);
	// 	ft_free((void**)attr);
	// }	
}

void ft_addalt(t_map *map, char *line, int i)
{
	int j;
	char **arr;

	// ask for map->alt[i] -> free
	map->alt[i] = malloc(sizeof(int) * map->wd + 1);
	if (!map->alt[i])
		exit(0);
	j = 0;
	arr = ft_split(line, ' ');
	if (line != 0)
	{
		while (arr[j])
		{
			map->alt[i][j] = ft_atoi(arr[j]);
			ft_trackht(map, i, j);
			j++;
		}
	}
	else
	{
		while (j < map->wd)
			map->alt[i][j++] = 0;
	}
	map->alt[i][j] = 0;
	ft_free((void **)arr);
}

void ft_getalt(t_map *map, char *file)
{
	int i;
	int fd;
	char *line;

	// Open and check fd -> free
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(0);
	// ask for altitude -> free
	map->alt = malloc(sizeof(int *) * map->ht + 1);
	if (!map->alt)
		exit(0);
	line = get_next_line(fd);
	while (line)
	{
		ft_addalt(map, line, i++);
		free(line);
		line = get_next_line(fd);
	}
	ft_addalt(map, 0, i);

	// read check
	// i = 0;
	// int j;
	// while (i <= map->ht)
	// {
	// 	j = 0;
	// 	while (j <= map->wd)
	// 		printf("%d  ", map->alt[i][j++]);
	// 	printf("\n");
	// 	i++;
	// }
	close(fd);
}

void ft_getdim(t_map *map, char *file)
{
	int fd;
	char *line;
	char **arr;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(0);
	map->wd = 0;
	map->ht = 0;
	line = get_next_line(fd);
	arr = ft_split(line, ' ');
	ft_free((void **)arr);
	while (arr[map->wd])
		map->wd++;
	while (line)
	{
		map->ht++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->top = 0;
	map->bottom = 0;
	printf("Dimension [%d][%d]\n", map->wd, map->ht);
}