#include "fdf.h"
#include <stdio.h>

int ft_close(t_map *map)
{
    int i;

    i = 0;
    while (i <= map->ht)
        free(map->px[i++]);
    free(map->px);
    free(map);
    mlx_destroy_window(map->mlx, map->mlx_win);
    return (1);
}

int ft_move(int keycode, t_map *map)
{
    if (keycode == 123 && map->x + ((map->wd + map->ht) * map->size * 2) + map->size * 2 > map->win_width / 2)
        map->x -= map->size * 2;
    else if (keycode == 124 && map->x - map->size * 2 < map->win_width / 2.0)
        map->x += map->size * 2;
    else if (keycode == 126 && map->y - (map->ht * map->size) + map->size < map->win_height / 2)
        map->y += map->size;
    else if (keycode == 125 && map->y + (map->ht * map->size) - map->size > map->win_height / 2)
        map->y -= map->size;
    ft_drawbg(map);
    ft_draw(map);
    return (0);
}

int ft_zoom(int key, t_map *map)
{
    if (key == 33 && map->size < 50)
    {
        map->size++;
        map->x += map->size * 2;
        map->y += map->size;
    }
    else if (key == 30 && map->size > 1)
    {
        map->size--;
        map->x -= map->size * 2;
        map->y -= map->size;
    }
    ft_drawbg(map);
    ft_draw(map);
    return (0);
}

int ft_keyhook(int key, t_map *map)
{
    int status;
    
    status = 0;
    ft_printf("key %d is pressed\n", key);
    if (key == 65307 || key == 53)
        status = ft_close(map);
    else if (key == 123 || key == 124 || key == 125 || key == 126)
        status = ft_move(key, map);
    else if (key == 30 || key == 33)
        ft_zoom(key, map);
    if (status == 1)
        exit(0);
    return (0);
}