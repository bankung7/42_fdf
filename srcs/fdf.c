#include "fdf.h"

int ft_setup(t_map *map)
{
    map->w_width = 800;
    map->w_height = 800;
    map->zoom = 20;
    map->xo = 25;
    map->yo = map->w_height / 2.0;
    return (0);
}

int ft_draw(t_map *map)
{
    map->x = 0;
    while (map->x < map->vh)
    {
        map->y = 0;
        while (map->y < map->vw)
        {
            ft_drawline(map, map->x, map->y + 1);
            map->y++;
        }
        map->x++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_map map;

    // Check argument
    if (argc != 2)
        ft_exit("Incorrect format : ./fdf [file.fdf]\n", 0, 0);

    // Get dimension
    ft_getdim(&map, argv[1]);
    printf("Map Dimension : [%d]x[%d]\n", map.vw, map.vh);

    // Get z and color
    ft_getpx(&map, argv[1]);
    // ft_read(&map);

    // Setup basic variable
    ft_setup(&map);

    // Initiate mlx
    map.mlx = mlx_init();
    map.win = mlx_new_window(map.mlx, map.w_width, map.w_height, "My Window");
    map.img.ptr = mlx_new_image(map.mlx, map.w_width, map.w_height);
    map.img.addr = mlx_get_data_addr(map.img.ptr, &map.img.bpp, &map.img.line_size, &map.img.endian);

    // draw bg
    ft_drawbg(&map, 0xaaaaaa);
    mlx_put_image_to_window(map.mlx, map.win, map.img.ptr, 0, 0);

    // draw line
    ft_draw(&map);
    mlx_put_image_to_window(map.mlx, map.win, map.img.ptr, 0, 0);

    // put to window and loop
    mlx_hook(map.win, 2, 1L << 2, ft_keyhook, &map);
    mlx_hook(map.win, 17, 1L << 17, ft_close, &map);
    mlx_loop(map.mlx);

    return (0);
}