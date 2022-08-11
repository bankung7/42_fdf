#include "fdf.h"
#include <stdio.h>

void ft_setup(t_map *map)
{   
    map->win_width = 800;
    map->win_height = 800;
    map->size = (float)(map->win_width - 50) / (float)(map->wd + map->ht) / 2.0;
    map->x = 25;
    map->top = 0;
    map->bottom = 0;
    map->highest = 0;
    // get color -> free
    // map->color = malloc(sizeof(sizeof(int*) * map->ht));
    // if (!map->color)
    //     exit(0);
    // while (i < map->wd)
    // {
    //     // build array -> free
    //     map->color[i] = malloc(sizeof(int) * map->wd);
    //     if (!map->color[i++])
    //         exit(0);
    // }
}
