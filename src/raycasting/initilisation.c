/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:12:08 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 13:21:46 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	initilize_ray2(t_data *data, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - data->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->pos_y) * ray->deltadist_y;
	}
}

void	initilize_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->raydir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray->raydir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (ray->raydir_x == 0)
		ray->deltadist_x = INT_MAX;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = INT_MAX;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
	initilize_ray2(data, ray);
}

void	initilisation(t_data *data, t_ray *ray, int x, int *hit_c)
{
	*hit_c = 0;
	initilize_ray(data, ray, x);
}
