/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:34 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/26 21:33:33 by tomecker         ###   ########.fr       */
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

int check_sprites(t_data *data, int x, int hit_c, t_ray ray)
{
    int i;

    i = 0;
    while(i < data->sprite_count)
    {
        if (ray.mapX == (int)data->sprites[i].x && ray.mapY == (int)data->sprites[i].y)
        {
            data->hit[x][hit_c].type = 'S';
            data->hit[x][hit_c].sprite_t = i;
            data->hit[x][hit_c].tex = data->sprites[i].tex;
            return (1);
        }
        i++;
    }
    return (0);
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
            if (check_sprites(data, x, hit_c, ray))
                hit_c++;
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
                if (newX < 0)
                    newX = 0;
                if (newY >= 10)
                    newY = 10 - 1;
                if (newX >= 14)
                    newX = 14 - 1;
                
                if (ft_strchr("KD", data->Map[(int)newY][(int)newX]))
                {
                    if (data->Map[(int)newY][(int)newX] == 'K')
                    {
                        data->hit[x][hit_c].tex = data->texture->DO;
                    }
                    else
                    {
                        data->hit[x][hit_c].tex = data->texture->D;
                    }
                    if (ray.side == 0)
                        data->hit[x][hit_c].distance = ray.sideDistX - 0.5 * ray.deltaDistX;
                    else
                        data->hit[x][hit_c].distance = ray.sideDistY - 0.5 * ray.deltaDistY;
                    
                    if(data->Map[(int)newY][(int)newX] == 'K' && newX == data->posX && newY == data->posY)
                        data->hit[x][hit_c].distance = 0;

                    data->hit[x][hit_c].type = data->Map[(int)newY][(int)newX];
                    get_texX(data, ray, x, hit_c);
                    hit_c++;
                }
            }
            if (ft_strchr("1F", data->Map[ray.mapY][ray.mapX]))
				        hit = 1;
        }

		if (ray.side == 0)
			data->hit[x][hit_c].distance = ray.sideDistX - ray.deltaDistX;
		else
			data->hit[x][hit_c].distance = ray.sideDistY - ray.deltaDistY;



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
        if (ray.rayDirX == data->dirX && ray.rayDirY == data->dirY)
            data->facing[x] = data->hit[x][0].type;

        get_texX(data, ray, x, hit_c);
        data->hit_count[x] = hit_c;
        x++;
    }
}
