#include "fdf.h"
#include <stdio.h>

void ft_setup(t_map *map)
{   
    map->win_width = 800;
    map->win_height = 800;
    map->size = (float)(map->win_width - 50) / (float)(map->wd + map->ht) / 2.0;
    map->pa = map->size * 1.5;
    map->x = 25;
    map->y = map->win_height / 2;
    map->top = 0;
    map->bottom = 0;
    map->highest = 0;
    map->kb = 0;
}

void    ft_drawbg(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->win_height)
    {
        j = 0;
        while (j < map->win_width)
            ft_put_pixel(map, i, j++, 0x0);
        i++;
    }
    mlx_put_image_to_window(map->mlx, map->mlx_win, map->mlx_img, 0, 0);
}