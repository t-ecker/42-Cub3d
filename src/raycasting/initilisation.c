/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:12:08 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 12:57:06 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	initilize_ray2(t_data *data, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - data->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - data->posY) * ray->deltaDistY;
	}
}

void	initilize_ray(t_data *data, t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->rayDirX = data->dirX + data->planeX * ray->cameraX;
	ray->rayDirY = data->dirY + data->planeY * ray->cameraX;
	ray->mapX = (int)data->posX;
	ray->mapY = (int)data->posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = INT_MAX;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = INT_MAX;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	initilize_ray2(data, ray);
}

void	initilisation(t_data *data, t_ray *ray, int x, int *hit_c)
{
	*hit_c = 0;
	initilize_ray(data, ray, x);
}
