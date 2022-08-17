#include "fdf.h"

int ft_close(t_map *map)
{
    ft_exit("Closing window\n", map, 0);
    return (0);
}

int ft_move(int keycode, t_map *map)
{
    if (keycode == 123 && map->x <= map->w_width / 2.)
        map->x += map->zoom;
    else if (keycode == 124 && map->x >= ((map->vw + map->vh) * cos(map->seta * 22. / 7. / 180.) * map->zoom) - (map->w_width / 2.))
        map->x -= map->zoom;
    else if (keycode == 125)
        map->y -= map->zoom;
    else if (keycode == 126)
        map->y += map->zoom;
    ft_drawbg(map, 0x0);
    ft_draw(map);
    return (0);
}

int ft_rotate(int keycode, t_map *map)
{
    if (keycode == 12)
        map->seta++;
    else
        map->seta--;
    ft_drawbg(map, 0x0);
    ft_draw(map);
    return (0);
}

int ft_keyhook(int keycode, t_map *map)
{
    printf("key is pressed %d\n", keycode);
    if (keycode == 53)
        ft_close(map);
    else if (keycode == 12 || keycode == 14)
        ft_rotate(keycode, map);
    else if (keycode >=123 && keycode <= 126)
        ft_move(keycode, map);
    return (0);
}