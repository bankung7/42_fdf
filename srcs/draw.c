#include "fdf.h"

void ft_put_pixel(t_map *map, int x, int y, int color)
{
    char *ptr;

    ptr = map->img.addr + (y * map->img.line_size) + (x * (map->img.bpp / 8));
    *(unsigned int *)ptr = color;
}

void ft_drawbg(t_map *map, int color)
{
    int i;
    int j;

    i = 0;
    ft_printf("Drawing bg\n");
    while (i < map->w_height)
    {
        j = 0;
        while (j < map->w_width)
            ft_put_pixel(map, i, j++, color);
        i++;
    }
}

// void ft_linelow(x0, y0, x1, y1)
// {
//     dx = x1 - x0;
//     dy = y1 - y0;
//     yi = 1;
//     if (dy < 0)
//     {
//         yi = -1;
//         dy = -dy;
//     }
//     D = (2 * dy) - dx;
//     y = y0;
//     while (x < x1)
//     {
//         ft_put_pixel(x, y);
//         if (D > 0)
//         {
//             y++;
//             D = D + (2 * (dy - dx));
//         }
//         else
//             D = D + 2 * dy;
//         x++;
//     }
// }

void ft_drawline(t_map *map, float x1, float y1)
{
    printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", map->x * map->zoom, map->y * map->zoom, x1 * map->zoom, y1 * map->zoom);

    while (map->y < y1 * map->zoom)
    {
        ft_put_pixel(map, map->x, map->y, 0xffffff);
        map->y++;
    }
    // if (fabsf(y1 - map->y) < fabsf(x1 - map->x))
    // {
    //     if (x0 > x1)
    //         ft_linelow(x1, y1, x0, y0);
    //     else
    //         ft_linelow(x0, y0, x1, y1);
    // }
    // else
    // {
    //     if (y0 > y1)
    //         ft_linehigh(x1, y1, x0, y0);
    //     else
    //         ft_linehigh(x0, y0, x1, y1);
    // }
}