/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:34 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 19:39:53 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	get_tex_x(t_data *data, t_ray ray, int x, int hc)
{
	if (ray.side == 0)
		data->texture->wall_x = data->pos_y \
			+ data->hit[x][hc].distance * ray.raydir_y;
	else
		data->texture->wall_x = data->pos_x \
			+ data->hit[x][hc].distance * ray.raydir_x;
	data->texture->wall_x -= floor(data->texture->wall_x);
	data->hit[x][hc].tex_x = data->texture->wall_x \
		* data->hit[x][hc].tex->height;
	if (ray.side == 0 && ray.raydir_x > 0)
		data->hit[x][hc].tex_x = data->hit[x][hc].tex->height \
			- data->hit[x][hc].tex_x - 1;
	if (ray.side == 1 && ray.raydir_y < 0)
		data->hit[x][hc].tex_x = data->hit[x][hc].tex->height \
			- data->hit[x][hc].tex_x - 1;
}

void	set_wall_attributes(t_data *data, t_ray ray, int x, int hit_c)
{
	if (ray.side == 0)
		data->hit[x][hit_c].distance = ray.sidedist_x - ray.deltadist_x;
	else
		data->hit[x][hit_c].distance = ray.sidedist_y - ray.deltadist_y;
	if (data->map[ray.map_y][ray.map_x] == 'F')
	{
		data->hit[x][hit_c].tex = data->texture->f;
		data->hit[x][hit_c].type = 'F';
	}
	else
	{
		if (ray.side && ray.raydir_y > 0)
			data->hit[x][hit_c].tex = data->texture->w;
		else if (ray.side && ray.raydir_y < 0)
			data->hit[x][hit_c].tex = data->texture->e;
		else if (!ray.side && ray.raydir_x < 0)
			data->hit[x][hit_c].tex = data->texture->n;
		else if (!ray.side && ray.raydir_x > 0)
			data->hit[x][hit_c].tex = data->texture->s;
		data->hit[x][hit_c].type = 'W';
	}
	get_tex_x(data, ray, x, hit_c);
}

void	castrays(t_data *data)
{
	int		x;
	t_ray	ray;
	int		hit;
	int		hit_c;

	x = 0;
	while (x < WIDTH)
	{
		initialization(data, &ray, x, &hit_c);
		hit = 0;
		while (hit == 0)
			hit = dda(data, &ray, x, &hit_c);
		set_wall_attributes(data, ray, x, hit_c);
		x++;
	}
}
