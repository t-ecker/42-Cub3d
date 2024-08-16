#include "../include/cubed.h"

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
	
		bresenham(start, end, cubed->walls);
		x++;
	}


}