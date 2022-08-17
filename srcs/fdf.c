#include "fdf.h"

int ft_setup(t_map *map)
{
    map->w_width = 800;
    map->w_height = 800;
    map->zoom = (float)(map->w_width - 20.) / (float)(map->vw + map->vh);
    if (map->zoom < 1.5)
        map->zoom = 1.5;
    map->seta = 30;
    map->pa = 1;
    map->x = (map->vw + map->vh) * cos(map->seta * 22. / 7. / 180.) * map->zoom;
    if (map->x < map->w_width)
        map->x = ((float)map->w_width - map->x) / 2.;
    else
        map->x = ((float)map->w_width - map->x) / 2.;
    map->y = map->w_height / 2.0;
    return (0);
}

int ft_draw(t_map *map)
{
    t_ace ace;

    ace.i = 0;
    while (ace.i < map->vh)
    {
        ace.j = 0;
        while (ace.j < map->vw)
        {
            if (ace.j < map->vw - 1)
                ft_drawline(map, &ace, ace.i, ace.j + 1);
            if (ace.i < map->vh - 1)
                ft_drawline(map, &ace, ace.i + 1, ace.j);
            ace.j++;
        }
        ace.i++;
        mlx_put_image_to_window(map->mlx, map->win, map->img.ptr, 0, 0);
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
    ft_drawbg(&map, 0x0);
    mlx_put_image_to_window(map.mlx, map.win, map.img.ptr, 0, 0);

    // ft_read(&map);

    // draw line
    ft_draw(&map);

    // put to window and loop
    mlx_hook(map.win, 2, 1L << 2, ft_keyhook, &map);
    mlx_hook(map.win, 17, 1L << 17, ft_close, &map);
    mlx_loop(map.mlx);

    return (0);
}