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

void	ft_color(t_map *map, int i, int j, char *px)
{
	int	x;
	int	c;
	int	pos;
	char	color;
	
	x = 0;
	c = 0;
	pos = 0;
	while (px[pos] && px[pos] != ',')
		pos++;
	if (pos > 0 && pos < (int)ft_strlen(px))
	{
		color = ft_toupper(px[ft_strlen(px) - x - 1]);
		while (pos + 1 + x < (int)ft_strlen(px) - 2)
		{
			if (ft_isdigit(color) == 1)
				c += (pow(16, x) * (color - '0'));
			else if ((color - 'A') >= 0 && (color - 'A') <= 5)
				c += (pow(16, x) * (color - 'A' + 10));
			map->px[i][j].color = c;
			x++;
			color = ft_toupper(px[ft_strlen(px) - x - 1]);
		}
	}
	else
		map->px[i][j].color = (int)(0xffffff);
}

void ft_trackht(t_map *map, int i, int j)
{
	int value;

	value = (i - j) * map->size - map->px[i][j].alt * map->pa;
	if (map->px[i][j].alt != 0)
	{
		// Something weird here for unin value
		if (value < map->top)
			map->top = value;
		if (map->bottom && value > map->bottom)
			map->bottom = value;
		if (map->px[i][j].alt > map->highest)
			map->highest = map->px[i][j].alt;
	}
}

void ft_addalt(t_map *map, char *line, int i)
{
	int j;
	char **arr;

	// ask for map->alt[i] -> free
	map->px[i] = malloc(sizeof(t_px) * (map->wd + 1));
	if (!map->px[i])
		exit(0);
	j = 0;
	arr = ft_split(line, ' ');
	if (line != 0)
	{
		while (j < map->wd && arr[j])
		{
			map->px[i][j].alt = ft_atoi(arr[j]);
			ft_trackht(map, i, j);
	       		ft_color(map, i, j, arr[j]);
			j++;
		}
	}
	else
	{
		while (j < map->wd)
			map->px[i][j++].alt = 0;
	}
	//map->px[i][j].alt = 0;
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
	map->top = 0;
	map->px = malloc(sizeof(t_px*) * (map->ht + 1));
	if (!map->px)
		exit(0);
	line = get_next_line(fd);
	while (line)
	{
		ft_addalt(map, line, i++);
		free(line);
		line = get_next_line(fd);
	}
	ft_addalt(map, 0, i);
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
	while (arr[map->wd])
		map->wd++;
	ft_free((void **)arr);
	while (line)
	{
		map->ht++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
