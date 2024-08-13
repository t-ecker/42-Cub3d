#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct s_ray
{
	double rayDirX;
	double sideDistX;
	double sideDistY;
	double rayDirY;
	double cameraX;
	int mapY;
	int mapX;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int side;
}	t_ray;

typedef struct s_data
{
	double posX;
	double posY;
	double planeX;
	double planeY;
	double dirX;
	double dirY;
	int worldMap[MAP_WIDTH][MAP_HEIGHT];
	double wallDistances[SCREEN_WIDTH];
}	t_data;

void castRays(t_data *data)
{
	int x;
	t_ray ray;
	int hit;
	
	x = 0;
    while (x < SCREEN_WIDTH)
	{
		hit = 0;
        ray.cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
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
            if (data->worldMap[ray.mapX][ray.mapY] > 0)
				hit = 1;
        }

		if (ray.side == 0)
			data->wallDistances[x] = ray.sideDistX - ray.deltaDistX;
		else
			data->wallDistances[x] = ray.sideDistY - ray.deltaDistY;

		x++;
    }
}

void	get_map(t_data *data)
{
	int Map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			data->worldMap[i][j] = Map[i][j];
		}
	}
}

void	init_data(t_data *data)
{
	get_map(data); //tmp

	data->posX = 2.5;
	data->posY = 2.5;

	data->dirX = 1.0;
	data->dirY = 0.0;
	
	data->planeX = 0.0;
	data->planeY = 0.66;
}

int main(void)
{
	t_data data;
	
	init_data(&data);
	castRays(&data);

    for (int x = 0; x < SCREEN_WIDTH; x++)
        printf("Ray %d: Distance to wall = %f\n", x, data.wallDistances[x]);

    return (0);
}
