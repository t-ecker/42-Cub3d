/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:23:20 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 12:16:00 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	move(t_ray *ray)
{
	if (ray->sideDistX < ray->sideDistY)
	{
		ray->sideDistX += ray->deltaDistX;
		ray->mapX += ray->stepX;
		ray->side = 0;
	}
	else
	{
		ray->sideDistY += ray->deltaDistY;
		ray->mapY += ray->stepY;
		ray->side = 1;
	}
}

void	cell_middle_pos(t_data *data, t_ray *ray, double *new_x, double *new_y)
{
	double	pos_x;
	double	pos_y;

	if (ray->side == 0)
	{
		pos_x = (ray->sideDistX - ray->deltaDistX) * ray->rayDirX + data->posX;
		pos_y = (ray->sideDistX - ray->deltaDistX) * ray->rayDirY + data->posY;
		*new_x = pos_x + ray->deltaDistX * 0.5 * ray->rayDirX;
		*new_y = pos_y + ray->deltaDistX * 0.5 * ray->rayDirY;
	}
	else
	{
		pos_x = (ray->sideDistY - ray->deltaDistY) * ray->rayDirX + data->posX;
		pos_y = (ray->sideDistY - ray->deltaDistY) * ray->rayDirY + data->posY;
		*new_x = pos_x + ray->deltaDistY * 0.5 * ray->rayDirX;
		*new_y = pos_y + ray->deltaDistY * 0.5 * ray->rayDirY;
	}
	if (*new_y < 0)
		*new_y = 0;
	if (*new_x < 0)
		*new_x = 0;
	if (*new_y >= data->input->map_height)
		*new_y = data->input->map_height - 1;
	if (*new_x >= data->input->map_width)
		*new_x = data->input->map_width - 1;
}

void	door_collision(t_data *data, t_ray *ray, int *hit_c, int x)
{
	double	new_x;
	double	new_y;

	cell_middle_pos(data, ray, &new_x, &new_y);
	if (ft_strchr("KD", data->Map[(int)new_y][(int)new_x]))
	{
		if (data->Map[(int)new_y][(int)new_x] == 'K')
			data->hit[x][*hit_c].tex = data->texture->DO;
		else
			data->hit[x][*hit_c].tex = data->texture->D;
		if (ray->side == 0)
			data->hit[x][*hit_c].distance = ray->sideDistX \
				- 0.5 * ray->deltaDistX;
		else
			data->hit[x][*hit_c].distance = ray->sideDistY \
				- 0.5 * ray->deltaDistY;
		if (data->Map[(int)new_y][(int)new_x] == 'K'
			&& new_x == data->posX && new_y == data->posY)
			data->hit[x][*hit_c].distance = 0;
		data->hit[x][*hit_c].type = data->Map[(int)new_y][(int)new_x];
		get_tex_x(data, *ray, x, *hit_c);
		(*hit_c)++;
	}
}

int	dda(t_data *data, t_ray *ray, int x, int *hit_c)
{
	int	hit;

	hit = 0;
	move(ray);
	if (check_sprites(data, x, *hit_c, *ray))
		(*hit_c)++;
	if (ft_strchr("KD", data->Map[ray->mapY][ray->mapX]))
		door_collision(data, ray, hit_c, x);
	if (ft_strchr("1F", data->Map[ray->mapY][ray->mapX]))
		hit = 1;
	return (hit);
}
