#include "fdf.h"

int ft_close(t_map *map)
{
    ft_exit("Closing window\n", map, 0);
    return (0);
}

int ft_move(int keycode, t_map *map)
{
    if (keycode == 123 && map->x + map->scale < map->w_width)
        map->x += map->scale;
    else if (keycode == 124 && map->x + map->scale > 0)
        map->x -= map->scale;
    else if (keycode == 125 && map->y + map->scale > 0)
        map->y -= map->scale;
    else if (keycode == 126 && map->y + map->scale < map->w_height)
        map->y += map->scale;
    else if (keycode == 31)
    {
        map->x = map->w_width / 2.;
        map->y = map->w_height / 2.;
    }
    ft_drawbg(map, 0x0);
    ft_draw(map);
    return (0);
}

int ft_rotate(int keycode, t_map *map)
{
    if (keycode == 34)
    {
        map->rx = 45;
        map->ry = 35;
        map->rz = 330;
    }
    else if (keycode == 35)
    {
        map->rx = 0;
        map->ry = 0;
        map->rz = 0;
    }
    else if (keycode == 0)
        map->ry += 5;
    else if (keycode == 2)
        map->ry -= 5;
    else if (keycode == 12)
        map->rx += 5;
    else if (keycode == 14)
        map->rx -= 5;
    else if (keycode == 6)
        map->rz += 5;
    else if (keycode == 8)
        map->rz -= 5;
    ft_drawbg(map, 0x0);
    ft_draw(map);
    return (0);
}

int ft_zoom(int keycode, t_map *map)
{
    if (keycode == 30 && map->scale + 2 < 20)
        map->scale += 2;
    else if (keycode == 33 && map->scale - 2 > 0)
        map->scale -= 2;
    ft_draw(map);
    return (0);
}

int ft_keyhook(int keycode, t_map *map)
{
    if (keycode == 53)
        ft_close(map);
    else if (keycode == 0 || keycode == 2 || keycode == 6 || keycode == 8 || keycode == 12 || keycode == 14 || keycode == 34 || keycode == 35)
        ft_rotate(keycode, map);
    else if ((keycode >= 123 && keycode <= 126) || keycode == 31)
        ft_move(keycode, map);
    else if (keycode == 30 || keycode == 33)
        ft_zoom(keycode, map);
    // printf("key : %d\n", keycode);
    return (0);
}