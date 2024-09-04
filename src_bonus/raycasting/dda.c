/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:23:20 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 13:33:27 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	move(t_ray *ray)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->deltadist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->sidedist_y += ray->deltadist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	check_boundaries(double *new_x, double *new_y, t_data *data)
{
	if (*new_y < 0)
		*new_y = 0;
	if (*new_x < 0)
		*new_x = 0;
	if (*new_y >= data->input->map_height)
		*new_y = data->input->map_height - 1;
	if (*new_x >= data->input->map_width)
		*new_x = data->input->map_width - 1;
}

void	cell_middle_pos(t_data *data, t_ray *ray, double *new_x, double *new_y)
{
	double	pos_x;
	double	pos_y;

	if (ray->side == 0)
	{
		pos_x = (ray->sidedist_x - ray->deltadist_x)
			* ray->raydir_x + data->pos_x;
		pos_y = (ray->sidedist_x - ray->deltadist_x)
			* ray->raydir_y + data->pos_y;
		*new_x = pos_x + ray->deltadist_x * 0.5 * ray->raydir_x;
		*new_y = pos_y + ray->deltadist_x * 0.5 * ray->raydir_y;
	}
	else
	{
		pos_x = (ray->sidedist_y - ray->deltadist_y)
			* ray->raydir_x + data->pos_x;
		pos_y = (ray->sidedist_y - ray->deltadist_y)
			* ray->raydir_y + data->pos_y;
		*new_x = pos_x + ray->deltadist_y * 0.5 * ray->raydir_x;
		*new_y = pos_y + ray->deltadist_y * 0.5 * ray->raydir_y;
	}
	check_boundaries(new_x, new_y, data);
}

void	door_collision(t_data *data, t_ray *ray, int *hit_c, int x)
{
	double	new_x;
	double	new_y;

	cell_middle_pos(data, ray, &new_x, &new_y);
	if (ft_strchr("KD", data->map[(int)new_y][(int)new_x]))
	{
		if (data->map[(int)new_y][(int)new_x] == 'K')
			data->hit[x][*hit_c].tex = data->texture->k;
		else
			data->hit[x][*hit_c].tex = data->texture->d;
		if (ray->side == 0)
			data->hit[x][*hit_c].distance = ray->sidedist_x \
				- 0.5 * ray->deltadist_x;
		else
			data->hit[x][*hit_c].distance = ray->sidedist_y \
				- 0.5 * ray->deltadist_y;
		if (data->map[(int)new_y][(int)new_x] == 'K'
			&& new_x == data->pos_x && new_y == data->pos_y)
			data->hit[x][*hit_c].distance = 0;
		data->hit[x][*hit_c].type = data->map[(int)new_y][(int)new_x];
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
	if (ft_strchr("KD", data->map[ray->map_y][ray->map_x]))
		door_collision(data, ray, hit_c, x);
	if (ft_strchr("1F", data->map[ray->map_y][ray->map_x]))
		hit = 1;
	return (hit);
}
