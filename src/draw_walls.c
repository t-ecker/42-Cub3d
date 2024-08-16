#include "../include/cubed.h"

int get_color(char hit_side)
{
    if (hit_side == 'n')
        return (0xE6E6FAFF);
    if (hit_side == 's')
        return (0xF08080FF);
    if (hit_side == 'w')
        return (0x90EE90FF);
    if (hit_side == 'e')
        return (0xFFC0CBFF);
    return (0);
}

void	draw_walls(t_cubed *cubed, t_data *data)
{
	int x;
	int height;
	t_point start;
	t_point end;

	x = 0;
	while (x < WIDTH)
	{
		start.x = x;
		end.x = x;

		height = HEIGHT / data->wallDistances[x];
		start.y = -height / 2 + HEIGHT / 2;
		end.y = height / 2 + HEIGHT / 2;
	
		bresenham(start, end, cubed->walls, get_color(data->hit_side[x]));
		x++;
	}
}