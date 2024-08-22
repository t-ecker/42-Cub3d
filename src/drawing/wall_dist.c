/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:34 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/22 11:34:50 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void    get_texX(t_data *data, t_ray ray, int x, int hc)
{
    

    if (ray.side == 0)
        data->texture->wall_x = data->posY + data->hit[x][hc].distance * ray.rayDirY;
    else
        data->texture->wall_x = data->posX + data->hit[x][hc].distance * ray.rayDirX;
    data->texture->wall_x -= floor(data->texture->wall_x);
    data->hit[x][hc].texX = data->texture->wall_x * data->hit[x][hc].tex->height;
    if (ray.side == 0 && ray.rayDirX > 0)
        data->hit[x][hc].texX = data->hit[x][hc].tex->height - data->hit[x][hc].texX - 1;
    if (ray.side == 1 && ray.rayDirY < 0)
        data->hit[x][hc].texX = data->hit[x][hc].tex->height - data->hit[x][hc].texX - 1;
    
}

void castRays(t_data *data)
{
	int x;
	t_ray ray;
	int hit;
    int hit_c;

	x = 0;
    while (x < WIDTH)
	{
        hit_c = 0;
        data->facing[x] = '0';
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

            if (ft_strchr("KD", data->Map[ray.mapY][ray.mapX]))
            {
                if (ft_strchr("KD", data->Map[ray.mapY][ray.mapX]))
                {
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
                    
                    if (ft_strchr("KD", data->Map[(int)newY][(int)newX]))
                    {
                        if (data->Map[(int)newY][(int)newX] == 'K')
                        {
                            data->hit[x][hit_c].tex = data->texture->DO;
                            data->hit[x][hit_c].type = 'K';
                        
                        }
                        else
                        {
                            data->hit[x][hit_c].tex = data->texture->D;
                            data->hit[x][hit_c].type = 'D';
                        }
                        if (ray.side == 0)
                            data->hit[x][hit_c].distance = ray.sideDistX - 0.5 * ray.deltaDistX;
                        else
                            data->hit[x][hit_c].distance = ray.sideDistY - 0.5 * ray.deltaDistY;
                        
                        if(data->Map[(int)newY][(int)newX] == 'K' && newX == data->posX && newY == data->posY)
                            data->hit[x][hit_c].distance = 0;

                        if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY)
                            data->facing[x] = data->hit[x][hit_c].type;
                        get_texX(data, ray, x, hit_c);
                        hit_c++;
                    }
                }
            }
            if (ft_strchr("1F", data->Map[ray.mapY][ray.mapX]))
				hit = 1;
        }
        
		if (ray.side == 0)
			data->hit[x][hit_c].distance = ray.sideDistX - ray.deltaDistX;
		else
			data->hit[x][hit_c].distance = ray.sideDistY - ray.deltaDistY;


        if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY && data->Map[ray.mapY][ray.mapX] == 'F' && data->facing[x] == '0')
            data->facing[x] = 'F';
        else if (data->facing[x] == '0')
            data->facing[x] = 'W';

        if (data->Map[ray.mapY][ray.mapX] == 'F')
        {
            data->hit[x][hit_c].tex = data->texture->F;
            data->hit[x][hit_c].type = 'F';
        }
        else
        {
            if (ray.side && ray.rayDirY > 0)
                data->hit[x][hit_c].tex = data->texture->w;
            else if(ray.side && ray.rayDirY < 0)
                data->hit[x][hit_c].tex = data->texture->e;
            else if (!ray.side && ray.rayDirX < 0)
                data->hit[x][hit_c].tex = data->texture->n;
            else if (!ray.side && ray.rayDirX > 0)
                data->hit[x][hit_c].tex = data->texture->s;
            data->hit[x][hit_c].type = 'W';
        }

        get_texX(data, ray, x, hit_c);
        data->hit_count[x] = hit_c;
        x++;
    }
}
