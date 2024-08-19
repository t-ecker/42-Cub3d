/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:34 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 14:17:08 by tecker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void    get_texX(t_data *data, t_ray ray, int x)
{
    

    if (ray.side == 0)
        data->texture->wall_x = data->posY + data->wallDistances[x] * ray.rayDirY;
    else
        data->texture->wall_x = data->posX + data->wallDistances[x] * ray.rayDirX;
    data->texture->wall_x -= floor(data->texture->wall_x);
    data->texX[x] = data->texture->wall_x * textureH;
    if (ray.side == 0 && ray.rayDirX > 0)
        data->texX[x] = textureH - data->texX[x] - 1;
    if (ray.side == 1 && ray.rayDirY < 0)
        data->texX[x] = textureH - data->texX[x] - 1;
    
}

void castRays(t_data *data)
{
	int x;
	t_ray ray;
	int hit;

	x = 0;
    while (x < WIDTH)
	{
        data->cdoor[x] = 0.0;
		hit = 0;
        ray.cameraX = 2 * x / (double)WIDTH - 1;
        ray.rayDirX = data->dirX + data->planeX * ray.cameraX;
        ray.rayDirY = data->dirY + data->planeY * ray.cameraX;

        ray.mapX = (int)data->posX;
        ray.mapY = (int)data->posY;

        if (ray.rayDirX == 0)
		    ray.deltaDistX = INT_MAX;
        else
            ray.deltaDistX = fabs(1 / ray.rayDirX);
        if (ray.rayDirY == 0)
            ray.deltaDistY = INT_MAX;
        else
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

//is the ray hitting something we dont want to see?
            if (data->Map[ray.mapY][ray.mapX] == 'K')
            {
                if (ray.side == 0)
                    data->cdoor[x] = ray.sideDistX - ray.deltaDistX;
                else
                    data->cdoor[x] = ray.sideDistY - ray.deltaDistY;   
            }
//did we hit something we want to see
            if (ft_strchr("1DF", data->Map[ray.mapY][ray.mapX]))
				hit = 1;
        }
        
//calc distance player -> wall
		if (ray.side == 0)
			data->wallDistances[x] = ray.sideDistX - ray.deltaDistX;
		else
			data->wallDistances[x] = ray.sideDistY - ray.deltaDistY;

//object player is facing (waht is the middle array hitting)
        if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->cdoor[x] > 0.0)
            data->facing[x] = 'K';
        else if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->Map[ray.mapY][ray.mapX] == 'F')
            data->facing[x] = 'F';
        else if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->Map[ray.mapY][ray.mapX] == 'D')
            data->facing[x] = 'D';
        else
            data->facing[x] = 'W';

//what side are we hitting?
        if (ray.side && ray.rayDirY > 0)
            data->hit_side[x] = 'w';
        else if(ray.side && ray.rayDirY < 0)
            data->hit_side[x] = 'e';
        else if (!ray.side && ray.rayDirX < 0)
            data->hit_side[x] = 'n';
        else if (!ray.side && ray.rayDirX > 0)
            data->hit_side[x] = 's';
        else if (data->Map[ray.mapY][ray.mapX] == 'F')
            data->hit_side[x] = 'F';

        if (data->Map[ray.mapY][ray.mapX] == 'D')
            data->hit_side[x] = 'D';

        get_texX(data, ray, x);
        x++;
    }
}
