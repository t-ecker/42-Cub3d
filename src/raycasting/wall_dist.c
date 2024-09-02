/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:34 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 22:02:51 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	get_tex_x(t_data *data, t_ray ray, int x, int hc)
{
	if (ray.side == 0)
		data->texture->wall_x = data->posY \
			+ data->hit[x][hc].distance * ray.rayDirY;
	else
		data->texture->wall_x = data->posX \
			+ data->hit[x][hc].distance * ray.rayDirX;
	data->texture->wall_x -= floor(data->texture->wall_x);
	data->hit[x][hc].texX = data->texture->wall_x \
		* data->hit[x][hc].tex->height;
	if (ray.side == 0 && ray.rayDirX > 0)
		data->hit[x][hc].texX = data->hit[x][hc].tex->height \
			- data->hit[x][hc].texX - 1;
	if (ray.side == 1 && ray.rayDirY < 0)
		data->hit[x][hc].texX = data->hit[x][hc].tex->height \
			- data->hit[x][hc].texX - 1;
}

int	check_sprites(t_data *data, int x, int hit_c, t_ray ray)
{
	int	i;

	i = 0;
	while (i < data->sprite_count)
	{
		if (ray.mapX == (int)data->sprites[i].x
			&& ray.mapY == (int)data->sprites[i].y)
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

void	set_wall_attributes(t_data *data, t_ray ray, int x, int hit_c)
{
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
		else if (ray.side && ray.rayDirY < 0)
			data->hit[x][hit_c].tex = data->texture->e;
		else if (!ray.side && ray.rayDirX < 0)
			data->hit[x][hit_c].tex = data->texture->n;
		else if (!ray.side && ray.rayDirX > 0)
			data->hit[x][hit_c].tex = data->texture->s;
		data->hit[x][hit_c].type = 'W';
	}
	get_tex_x(data, ray, x, hit_c);
	data->hit_count[x] = hit_c;
}

void	castrays(t_data *data)
{
	int		x;
	t_ray	ray;
	int		hit;
	int		hit_c;
	int		i;

	x = 0;
	while (x < WIDTH)
	{
		initilisation(data, &ray, x, &hit_c);
		hit = 0;
		while (hit == 0)
			hit = dda(data, &ray, x, &hit_c);
		set_wall_attributes(data, ray, x, hit_c);
		i = 0;
		if (x == WIDTH / 2)
		{
			data->facing[x] = data->hit[x][0].type;
			while (data->hit[x][i].type == 'K')
				i++;
			if (data->hit[x][i].type == 'S')
				data->facing[x] = 'S';
		}
		x++;
	}
}
