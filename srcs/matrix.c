#include "fdf.h"

void ft_rotx(t_map *map, t_line *line)
{
    float v;
    float x;
    float y;
    float z;

    v = map->rx * 3.1416 / 180.;
    x = line->x0;
    y = line->y0;
    z = line->z0;
    line->x0 = x;
    line->y0 = y * cos(v) - z * sin(v);
    line->z0 = y * sin(v) + z * cos(v);
    x = line->x1;
    y = line->y1;
    z = line->z1;
    line->x1 = x;
    line->y1 = y * cos(v) - z * sin(v);
    line->z1 = y * sin(v) + z * cos(v);
}

void ft_roty(t_map *map, t_line *line)
{
    float v;
    float x;
    float y;
    float z;

    v = map->ry * 3.1416 / 180.;
    x = line->x0;
    y = line->y0;
    z = line->z0;
    line->x0 = x * cos(v) + z * sin(v);
    line->y0 = y;
    line->z0 = x * -sin(v) + z * cos(v);
    x = line->x1;
    y = line->y1;
    z = line->z1;
    line->x1 = x * cos(v) + z * sin(v);
    line->y1 = y;
    line->z1 = x * -sin(v) + z * cos(v);
}

void ft_rotz(t_map *map, t_line *line)
{
    float v;
    float x;
    float y;

    v = map->rz * 3.1416 / 180.;
    x = line->x0;
    y = line->y0;
    line->x0 = x * cos(v) - y * sin(v);
    line->y0 = x * sin(v) + y * cos(v);
    x = line->x1;
    y = line->y1;
    line->x1 = x * cos(v) - y * sin(v);
    line->y1 = x * sin(v) + y * cos(v);
}

void ft_isometric(t_line *line)
{
    float x;
    float y;
    float z;

    x = line->x0;
    y = line->y0;
    z = line->z0;
    line->x0 = x * sqrt(2) / 2 + y * -sqrt(2) / 2;
    line->y0 = x * sqrt(6) / 6 + y * sqrt(6) / 6 - z * sqrt(6) / 3;
    line->z0 = x * sqrt(3) / 3 + y * sqrt(3) / 3 + z * sqrt(3) / 3;
    x = line->x1;
    y = line->y1;
    z = line->z1;
    line->x1 = x * sqrt(2) / 2 + y * -sqrt(2) / 2;
    line->y1 = x * sqrt(6) / 6 + y * sqrt(6) / 6 - z * sqrt(6) / 3;
    line->z1 = x * sqrt(3) / 3 + y * sqrt(3) / 3 + z * sqrt(3) / 3;
}

void ft_2d(t_map *map, t_line *line)
{
    //ft_isometric(line);
    ft_rotx(map, line);
    ft_roty(map, line);
    ft_rotz(map, line);
    line->x0 = (line->x0 * map->scale) + map->x;
    line->y0 = (line->y0 * map->scale) + map->y;
    line->x1 = (line->x1 * map->scale) + map->x;
    line->y1 = (line->y1 * map->scale) + map->y;
}