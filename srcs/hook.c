#include "fdf.h"

int ft_close(t_map *map)
{
    ft_exit("Closing window\n", map, 0);
    return (0);
}

int ft_keyhook(int keycode, t_map *map)
{
    if (keycode == 53)
        ft_close(map);
    return (0);
}