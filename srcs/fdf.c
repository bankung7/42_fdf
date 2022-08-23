#include "fdf.h"

int ft_setup(t_map *map)
{
    map->rx = 45;
    map->ry = 35;
    map->rz = 330;
    map->w_width = 800;
    map->w_height = 800;
    if (map->vw > map->vh)
        map->scale = (float)map->w_width / (float)(map->vw + map->vh);
    else
        map->scale = (float)map->w_height / (float)(map->vw + map->vh);
    map->lenx = (float)map->vw / 2.;
    map->leny = (float)map->vh / 2.;
    map->x = map->w_width / 2.;
    map->y = map->w_height / 2.;
    map->pa = 1;
    return (0);
}

void ft_menu(t_map *map)
{
   mlx_string_put(map->mlx, map->win, 20, 20, 0xFFFFFF, "Rx : q or e");
   mlx_string_put(map->mlx, map->win, 20, 40, 0xFFFFFF, "Ry : a or d");
   mlx_string_put(map->mlx, map->win, 20, 60, 0xFFFFFF, "Rz : z or c");
   mlx_string_put(map->mlx, map->win, 20, 80, 0xFFFFFF, "Reset center : o");
   mlx_string_put(map->mlx, map->win, 20, 100, 0xFFFFFF, "Parallel : p");
   mlx_string_put(map->mlx, map->win, 20, 120, 0xFFFFFF, "Isometric : i");
   mlx_string_put(map->mlx, map->win, 20, 140, 0xFFFFFF, "Zoom : [ or ]");
}

int ft_draw(t_map *map)
{
    t_ace ace;

    ft_drawbg(map, 0x0);
    ace.i = 0;
    while (ace.i < map->vh)
    {
        ace.j = 0;
        while (ace.j < map->vw)
        {
            if (ace.i < map->vh - 1)
                ft_drawline(map, &ace, ace.j, ace.i + 1);
            if (ace.j < map->vw - 1)
                ft_drawline(map, &ace, ace.j + 1, ace.i);
            ace.j++;
        }
        ace.i++;
    }
    mlx_put_image_to_window(map->mlx, map->win, map->img.ptr, 0, 0);
    ft_menu(map);
    return (0);
}

int main(int argc, char **argv)
{
    t_map map;

    if (argc != 2)
        ft_exit("Incorrect format : ./fdf [file.fdf]\n", 0, 0);
    ft_getdim(&map, argv[1]);
    ft_getpx(&map, argv[1]);
    ft_setup(&map);
    map.mlx = mlx_init();
    map.win = mlx_new_window(map.mlx, map.w_width, map.w_height, "My Window");
    map.img.ptr = mlx_new_image(map.mlx, map.w_width, map.w_height);
    map.img.addr = mlx_get_data_addr(map.img.ptr, &map.img.bpp, &map.img.line_size, &map.img.endian);
    ft_draw(&map);
    mlx_hook(map.win, 2, 1L << 2, ft_keyhook, &map);
    mlx_hook(map.win, 17, 1L << 17, ft_close, &map);
    mlx_loop(map.mlx);
    return (0);
}