/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:34 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/22 01:10:04 by dolifero         ###   ########.fr       */
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

void cast_one_ray(t_data *data, char *str, int x)
{
    t_ray ray;
    int hit;

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
        ray.sideDistX = ((ray.mapX + 1.0 - data->posX)) * ray.deltaDistX;
    }
    if (ray.rayDirY < 0)
    {
        ray.stepY = -1;
        ray.sideDistY = ((data->posY - ray.mapY)) * ray.deltaDistY;
    }
    else
    {
        ray.stepY = 1;
        ray.sideDistY = ((ray.mapY + 1.0 - data->posY)) * ray.deltaDistY;
    }

    while (hit < 1)
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

        if (ft_strchr(str, data->Map[ray.mapY][ray.mapX]))
        {
            hit++;
            double posX;
            double posY;
            double newX;
            double newY;
            if (ray.side == 0)
            {
                posX = (ray.sideDistX - ray.deltaDistX) * ray.rayDirX + data->posX;
                posY = (ray.sideDistX - ray.deltaDistX) * ray.rayDirY + data->posY;
                newX = posX + ray.deltaDistX * 0.5 * ray.rayDirX;
                newY = posY + ray.deltaDistX * 0.5 * ray.rayDirY;
            }
            else
            {
                posX = (ray.sideDistY - ray.deltaDistY) * ray.rayDirX + data->posX;
                posY = (ray.sideDistY - ray.deltaDistY) * ray.rayDirY + data->posY;
                newX = posX + ray.deltaDistY * 0.5 * ray.rayDirX;
                newY = posY + ray.deltaDistY * 0.5 * ray.rayDirY;
            }
            if (newY < 0)
                newY = 0;
            if (newX < 0) newX = 0;
            if (newY >= 10)
                newY = 10 - 1;
            if (newX >= 14) newX = 14 - 1;

            if (ft_strchr(str, data->Map[(int)newY][(int)newX]))
            {
                if (data->Map[(int)newY][(int)newX] == 'K')
                    data->ttu[x] = 'K';
                else
                    data->ttu[x] = 'D';
                if (ray.side == 0)
                    data->wallDistances[x] = ray.sideDistX - 0.5 * ray.deltaDistX;
                else if(data->Map[(int)newY][(int)newX] == 'K' && newX == data->posX && newY == data->posY)
                    data->wallDistances[x] = 0;
                else
                    data->wallDistances[x] = ray.sideDistY - 0.5 * ray.deltaDistY;
            }
            else
            {
                data->ttu[x] = '0';
                if (ray.side)
                    ray.side--;
                else
                    ray.side++;
            }
        }

    }
    if (ray.side && ray.rayDirY > 0)
        data->hit_side[x] = 'w';
    else if(ray.side && ray.rayDirY < 0)
        data->hit_side[x] = 'e';
    else if (!ray.side && ray.rayDirX < 0)
        data->hit_side[x] = 'n';
    else if (!ray.side && ray.rayDirX > 0)
        data->hit_side[x] = 's';
    get_texX(data, ray, x);
}

void castRays(t_data *data)
{
	int x;
	t_ray ray;
	int hit;

	x = 0;
    while (x < WIDTH)
	{
        data->facing[x] = '0';
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
            if (ft_strchr("KD", data->Map[ray.mapY][ray.mapX]))
            {
                if (ray.side == 0)
                    data->cdoor[x] = ray.sideDistX - ray.deltaDistX;
                else
                    data->cdoor[x] = ray.sideDistY - ray.deltaDistY;

                if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->Map[ray.mapY][ray.mapX] == 'K')
                    data->facing[x] = 'K';
                else if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->Map[ray.mapY][ray.mapX] == 'D')
                    data->facing[x] = 'D';
            }
//did we hit something we want to see
            if (ft_strchr("1F", data->Map[ray.mapY][ray.mapX]))
				hit = 1;
        }

//calc distance player -> wall
		if (ray.side == 0)
			data->wallDistances[x] = ray.sideDistX - ray.deltaDistX;
		else
			data->wallDistances[x] = ray.sideDistY - ray.deltaDistY;

//object player is facing (waht is the middle array hitting)
        if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->Map[ray.mapY][ray.mapX] == 'F' && data->facing[x] == '0')
            data->facing[x] = 'F';
        else if (data->facing[x] == '0')
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

        if (data->Map[ray.mapY][ray.mapX] == 'F')
            data->ttu[x] = 'F';
        else
            data->ttu[x] = '0';

        get_texX(data, ray, x);
        x++;
    }
}
