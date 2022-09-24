/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:08:33 by vnilprap          #+#    #+#             */
/*   Updated: 2022/09/24 22:18:11 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (map)
	{
		if (map->img.ptr)
			mlx_destroy_image(map->mlx, map->img.ptr);
		if (map->win)
			mlx_destroy_window(map->mlx, map->win);
		if (map->px)
		{
			while (i < map->vh)
				free(map->px[i++]);
			free(map->px);
		}
		free(map);
	}
	ft_putstr_fd(str, n);
	exit(n);
}
