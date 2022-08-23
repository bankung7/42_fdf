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
    while (i < map->w_height)
    {
        j = 0;
        while (j < map->w_width)
            ft_put_pixel(map, i, j++, color);
        i++;
    }
    mlx_put_image_to_window(map->mlx, map->win, map->img.ptr, 0, 0);
}

void ft_linehigh(t_map *map, t_line *line)
{
    float xi;

    line->dx = line->x1 - line->x0;
    line->dy = line->y1 - line->y0;
    xi = 1;
    if (line->dx < 0)
    {
        xi = -1;
        line->dx = -line->dx;
    }
    line->p = (2.0 * line->dx) - line->dy;
    while (line->y0 < line->y1)
    {
        if (line->x0 >= 0 && line->x0 < map->w_width && line->y0 >= 0 && line->y0 < map->w_height)
        {
            ft_put_pixel(map, line->x0, line->y0, line->color0);
        }
        if (line->p > 0)
        {
            line->x0 += xi;
            line->p += (2.0 * (line->dx - line->dy));
        }
        else
            line->p += 2.0 * line->dx;
        line->y0++;
    }
}

void ft_linelow(t_map *map, t_line *line)
{
    float yi;

    line->dx = line->x1 - line->x0;
    line->dy = line->y1 - line->y0;
    yi = 1;
    if (line->dy < 0)
    {
        yi = -1;
        line->dy = -line->dy;
    }
    line->p = (2.0 * line->dy) - line->dx;
    while (line->x0 < line->x1)
    {
        if (line->x0 >= 0 && line->x0 < map->w_width && line->y0 >= 0 && line->y0 < map->w_height)
        {
            ft_put_pixel(map, line->x0, line->y0, line->color0);
        }
        if (line->p > 0)
        {
            line->y0 += yi;
            line->p += (2.0 * (line->dy - line->dx));
        }
        else
            line->p += 2.0 * line->dy;
        line->x0++;
    }
}

void ft_swap(t_line *line, void (*f)(t_map *, t_line *), t_map *map)
{
    int x;
    unsigned int c;

    x = line->x0;
    line->x0 = line->x1;
    line->x1 = x;
    x = line->y0;
    line->y0 = line->y1;
    line->y1 = x;
    c = line->color0;
    line->color0 = line->color1;
    line->color1 = c;
    f(map, line);
}

void ft_drawline(t_map *map, t_ace *ace, float x1, float y1)
{
    t_line line;

    line.x0 = ace->j - map->lenx;
    line.y0 = ace->i - map->leny;
    line.z0 = map->px[ace->i][ace->j].z;
    line.color0 = map->px[ace->i][ace->j].color;
    line.x1 = x1 - map->lenx;
    line.y1 = y1 - map->leny;
    line.z1 = map->px[(int)y1][(int)x1].z;
    line.color1 = map->px[ace->i][ace->j].color;
    ft_2d(map, &line);
    // printf("[%.2f][%.2f] -> [%.2f][%.2f]\n", line.x0, line.y0, line.x1, line.y1);
    if (fabsf(line.y1 - line.y0) < fabsf(line.x1 - line.x0))
    {
        if (line.x0 > line.x1)
            ft_swap(&line, ft_linelow, map);
        else
            ft_linelow(map, &line);
    }
    else
    {
        if (line.y0 > line.y1)
            ft_swap(&line, ft_linehigh, map);
        else
            ft_linehigh(map, &line);
    }
}
