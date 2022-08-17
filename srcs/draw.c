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

void ft_linehigh(t_map *map, t_line *line)
{
    float x;
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
    x = line->x0;
    while (line->y0 < line->y1)
    {
        if (x >= 0 && x < map->w_width && line->y0 >= 0 && line->y0 < map->w_height)
            ft_put_pixel(map, x, line->y0, 0xFF000F);
        if (line->p > 0)
        {
            x += xi;
            line->p += (2.0 * (line->dx - line->dy));
        }
        else
            line->p += 2.0 * line->dx;
        line->y0++;
    }
}

void ft_linelow(t_map *map, t_line *line)
{
    float y;
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
    y = line->y0;
    while (line->x0 < line->x1)
    {
        if (line->x0 >= 0 && line->x0 < map->w_width && y >= 0 && y < map->w_height)
            ft_put_pixel(map, line->x0, y, 0xFFFFFF);
        if (line->p > 0)
        {
            y += yi;
            line->p += (2.0 * (line->dy - line->dx));
        }
        else
            line->p += 2.0 * line->dy;
        line->x0++;
    }
}

void ft_swap(t_line *line)
{
    int x;

    x = line->x0;
    line->x0 = line->x1;
    line->x1 = x;
    x = line->y0;
    line->y0 = line->y1;
    line->y1 = x;
}

void ft_drawline(t_map *map, t_ace *ace, float x1, float y1)
{
    float st;
    t_line line;

    st = map->seta * 22. / 7. / 180.;
    line.x0 = map->x + (ace->i + ace->j) * map->zoom * cos(st);
    line.y0 = map->y + (ace->i - ace->j) * map->zoom * sin(st) - map->px[ace->i][ace->j].z * map->pa;
    line.x1 = map->x + (x1 + y1) * map->zoom * cos(st);
    line.y1 = map->y + (x1 - y1) * map->zoom * sin(st) - map->px[(int)x1][(int)y1].z * map->pa;

    // printf("[%.2f][%.2f] -> [%.2f][%.2f]\n", line.x0, line.y0, line.x1, line.y1);
    if (fabsf(line.y1 - line.y0) < fabsf(line.x1 - line.x0))
    {
        if (line.x0 > line.x1)
        {
            ft_swap(&line);
            ft_linelow(map, &line);
        }
        else
            ft_linelow(map, &line);
    }
    else
    {
        if (line.y0 > line.y1)
        {
            ft_swap(&line);
            ft_linehigh(map, &line);
        }
        else
            ft_linehigh(map, &line);
    }
}