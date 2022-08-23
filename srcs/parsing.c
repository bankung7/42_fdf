#include "fdf.h"

void ft_color(t_map *map, int i, int j, char *px)
{
    int x;
    int c;
    int pos;
    char color;

    x = 0;
    c = 0;
    pos = 0;
    while (px[pos] && px[pos] != ',')
        pos++;
    if (pos > 0 && pos < (int)ft_strlen(px))
    {
        color = ft_toupper(px[ft_strlen(px) - x - 1]);
        while (pos + 1 + x < (int)ft_strlen(px) - 2)
        {
            if (ft_isdigit(color) == 1)
                c += (pow(16, x) * (color - '0'));
            else if ((color - 'A') >= 0 && (color - 'A') <= 5)
                c += (pow(16, x) * (color - 'A' + 10));
            map->px[i][j].color = c;
            x++;
            color = ft_toupper(px[ft_strlen(px) - x - 1]);
        }
    }
    else
        map->px[i][j].color = (int)(0xffffff);
}

int ft_getz(t_map *map, char *line, int i)
{
    int j;
    char **arr;

    map->px[i] = malloc(sizeof(t_px) * (map->vw));
    if (!map->px[i])
        ft_exit("Cannot allocate memory\n", map, 0);
    j = 0;
    arr = ft_split(line, ' ');
    while (j < map->vw)
    {
        if (!arr[j])
            map->px[i][j].z = 0;
        else
            map->px[i][j].z = ft_atoi(arr[j]);
        ft_color(map, i, j, arr[j]);
        j++;
    }
    return (0);
}

int ft_getpx(t_map *map, char *file)
{
    int i;
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        ft_exit("Cannot open the file\n", 0, 0);
    map->px = malloc(sizeof(t_px *) * (map->vh));
    if (!map->px)
        ft_exit("Cannot allocate memory\n", 0, 0);
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        ft_getz(map, line, i++);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}

int ft_getdim(t_map *map, char *file)
{
    int fd;
    char *line;
    char **arr;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        ft_exit("Cannot open the file\n", 0, 0);
    map->vw = 0;
    map->vh = 0;
    line = get_next_line(fd);
    arr = ft_split(line, ' ');
    while (arr[map->vw])
        map->vw++;
    ft_free((void **)arr);
    while (line)
    {
        map->vh++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}