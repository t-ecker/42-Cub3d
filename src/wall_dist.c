#include "../include/cubed.h"

void castRays(t_data *data)
{
	int x;
	t_ray ray;
	int hit;
	
	x = 0;
    while (x < WIDTH)
	{
		hit = 0;
        ray.cameraX = 2 * x / (double)WIDTH - 1;
        ray.rayDirX = data->dirX + data->planeX * ray.cameraX;
        ray.rayDirY = data->dirY + data->planeY * ray.cameraX;

        ray.mapX = (int)data->posX;
        ray.mapY = (int)data->posY;

        ray.deltaDistX = fabs(1 / ray.rayDirX);
       	ray.deltaDistY = fabs(1 / ray.rayDirY);



        if (ray.rayDirX < 0)
		{
            ray.stepX = -1;
            ray.sideDistX = (data->posX - ray.mapX) * ray.deltaDistX;
        }
		else
		{
            ray.stepX = 1;
            ray.sideDistX = (ray.mapX + 1.0 - data->posX) * ray.deltaDistX;
        }
        if (ray.rayDirY < 0)
		{
            ray.stepY = -1;
            ray.sideDistY = (data->posY - ray.mapY) * ray.deltaDistY;
        }
		else
		{
            ray.stepY = 1;
            ray.sideDistY = (ray.mapY + 1.0 - data->posY) * ray.deltaDistY;
        }

        while (hit == 0)
		{
            if (ray.sideDistX < ray.sideDistY)
			{
                ray.sideDistX += ray.deltaDistX;
                ray.mapX += ray.stepX;
                ray.side = 0;
            }
			else
			{
                ray.sideDistY += ray.deltaDistY;
                ray.mapY += ray.stepY;
                ray.side = 1;
            }
            if (data->Map[ray.mapY][ray.mapX] == '1')
				hit = 1;
        }

		if (ray.side == 0)
			data->wallDistances[x] = ray.sideDistX - ray.deltaDistX;
		else
			data->wallDistances[x] = ray.sideDistY - ray.deltaDistY;

        if (ray.side && ray.rayDirY > 0)
            data->hit_side[x] = 'w';
        else if(ray.side && ray.rayDirY < 0)
            data->hit_side[x] = 'e';
        else if (!ray.side && ray.rayDirX < 0)
            data->hit_side[x] = 'n';
        else if (!ray.side && ray.rayDirX > 0)
            data->hit_side[x] = 's';

		x++;
    }
}