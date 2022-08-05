#include "fdf.h"

void ft_put_pixel(t_img *img, int x, int y, int color)
{
	char *ptr;

	ptr = img->addr + (y * img->line_bytes + x * (img->pixel_bits / 8));
	*(int *)ptr = color;
}

void ft_draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx;
	int dy;
	int p;
	int r;

	r = 0;
	dx = (x1 - x0);
	dy = (y1 - y0);
	if (dx > dy)
	{
		if (dy < 0)
		{
			r = 1;
			dy = -dy;
		}
		p = (2 * dy) - dx;
		while (x0 <= x1)
		{
			ft_put_pixel(img, x0, y0, color);
			x0++;
			if (p >= 0)
			{
				if (r == 1)
					y0--;
				else
					y0++;
				p += 2 * (dy - dx);
			}
			else
				p += 2 * dy;
		}
	}
	else
	{
		if (dx < 0)
		{
			r = 1;
			dx = -dx;
		}
		p = (2 * dx) - dy;
		while (y0 <= y1)
		{
			ft_put_pixel(img, x0, y0, color);
			y0++;
			if (p >= 0)
			{
				if (r == 1)
					x0--;
				else
					x0++;
				p += 2 * (dx - dy);
			}
			else
				p += 2 * dx;
		}
	}
}

void ft_plotlinelow(t_img *img, t_info info, t_line line)
{
	line.dx = line.x1 - line.x0;
	line.dy = line.y1 - line.y0;
	if (line.dy < 0)
	{
		line.r = 1;
		line.dy = -line.dy;
	}
	line.d = (2 * line.dy) - line.dx;
	while (line.x0 <= line.x1)
	{
		ft_put_pixel(img, line.x0, line.y0, info.color);
		line.x0++;
		if (line.d > 0)
		{
			if (line.r == 1)
				line.y0--;
			else
				line.y0++;
			line.d = line.d + (2 * (line.dy - line.dx));
		}
		else
			line.d = line.d + 2 * line.dy;
	}
}

void ft_plotlinehigh(t_img *img, t_info info, t_line line)
{
	line.dx = line.x1 - line.x0;
	line.dy = line.y1 - line.y0;
	if (line.dx < 0)
	{
		line.r = 1;
		line.dx = -line.dx;
	}
	line.d = (2 * line.dx) - line.dy;
	while (line.y0 <= line.y1)
	{
		ft_put_pixel(img, line.x0, line.y0, info.color);
		line.y0++;
		if (line.d >= 0)
		{
			if (line.r == 1)
				line.x0--;
			else
				line.x0++;
			line.d += 2 * (line.dx - line.dy);
		}
		else
			line.d += 2 * line.dx;
	}
}

void ft_plotline(t_img *img, t_info info, t_ace ace, int r)
{
	t_line line;
	line.x0 = info.x;
	line.y0 = info.y - info.z[ace.j][ace.i] * info.m;
	line.x1 = info.x + info.size * r;
	if (r == 1)
		line.y1 = (info.y + info.size / 2) - info.z[ace.j][ace.i + 1] * info.m;
	else if (r == -1)
		line.y1 = (info.y + info.size / 2) - info.z[ace.j + 1][ace.i] * info.m;
	if (abs(line.y1 - line.y0) < abs(line.x1 - line.x0))
	{
		if (line.x0 > line.x1)
			ft_plotlinelow(img, info, (t_line){line.x1, line.y1, line.x0, line.y0, 0, 0, 0, 0});
		else
			ft_plotlinelow(img, info, (t_line){line.x0, line.y0, line.x1, line.y1, 0, 0, 0, 0});
	}
	else
	{
		if (line.y0 > line.y1)
			ft_plotlinehigh(img, info, (t_line){line.x1, line.y1, line.x0, line.y0, 0, 0, 0, 0});
		else
			ft_plotlinehigh(img, info, (t_line){line.x0, line.y0, line.x1, line.y1, 0, 0, 0, 0});
	}
}

void ft_draw_main(t_img *img, t_info info)
{
	int i = 0;
	int j = 0;
	// int f = 5;

	while (j <= info.vy - 1)
	{
		while (i <= info.vx - 1)
		{
			// Draw right line
			if (i != info.vx - 1)
				ft_plotline(img, info, (t_ace){i, j}, 1);
			// Draw left line
			if (j != info.vy - 1)
				ft_plotline(img, info, (t_ace){i, j}, -1);
			info.x += info.size;
			info.y += (info.size / 2);
			i++;
		}
		info.y -= ((info.size / 2) * (i - 1));
		info.x -= (info.size * (i + 1));
		i = 0;
		j++;
	}
}

int main(int argc, char **argv)
{
	t_data data;
	t_img img;
	t_info info;

	if (argc != 2)
		return (0);

	int width = 1000;
	int height = 800;

	// create mlx_ptr
	data.mlx = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx, width, height, "My window");
	img.img = mlx_new_image(data.mlx, width, height);

	img.addr = mlx_get_data_addr(img.img, &img.pixel_bits, &img.line_bytes, &img.endian);

	// got vx, vy and z from parsing
	info = *ft_parsing(argv[1]);
	info.color = 0xFFFFFF;
	info.size = (width - 200) / (info.vx + info.vy);
	info.x = info.vy * info.size + 100;
	info.y = (height - info.vx * info.size) / 2;
	ft_printf("highest point : %d\n", info.m);
	ft_printf("image size %d x %d\n", info.vx, info.vy);
	info.m = 3;

	ft_draw_main(&img, info);

	mlx_put_image_to_window(data.mlx, data.win_ptr, img.img, 0, 0);
	mlx_loop(data.mlx);
}
