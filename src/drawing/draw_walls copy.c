/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:38 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 22:52:39 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	redraw(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	setplane(data);
	castrays(data);
	clear_image(data->cubed->walls);
	clear_image(data->cubed->info);
	draw(data);
}

void	print_wall_line(t_data *data, int x, int hit_c)
{
	int	color;

	while (data->texture->startY < data->texture->endY)
	{
		data->texture->texY = (int)data->texture->tex_pos \
			% data->hit[x][hit_c].tex->height;
		data->texture->tex_pos += data->texture->step;
		if (is_pixel_transp(data->cubed->walls, x, data->texture->startY))
		{
			color = get_texture_color(data->hit[x][hit_c].tex,
					data->hit[x][hit_c].texX, data->texture->texY);
			if (color != 0x00000000)
				my_put_pixel(data->cubed->walls, x, data->texture->startY,
					add_fog(color, data->weapon, INT_MAX,
						data->hit[x][hit_c].distance));
		}
		data->texture->startY++;
	}
}

void	draw_walls(t_data *data, int x, int hit_c)
{
	int	height;

	height = HEIGHT / data->hit[x][hit_c].distance;
	data->texture->startY = -height / 2 + HEIGHT / 2;
	if (data->texture->startY < 0)
		data->texture->startY = 0;
	data->texture->endY = height / 2 + HEIGHT / 2;
	if (data->texture->endY >= HEIGHT)
		data->texture->endY = HEIGHT - 1;
	data->texture->step = 1.0 * data->hit[x][hit_c].tex->height / height;
	data->texture->tex_pos = (data->texture->startY \
		- HEIGHT / 2 + height / 2) * data->texture->step;
	print_wall_line(data, x, hit_c);
}

void	check_info(t_data *data, int x)
{
	if (data->facing[x] == 'F' && data->hit[x][0].type == 'F'
		&& data->hit[x][0].distance < 1.2)
		draw_info(data, 'F');
	if ((data->facing[x] == 'D' && data->hit[x][0].type == 'D'
		&& data->hit[x][0].distance < 1.2))
		draw_info(data, 'D');
	if ((data->facing[x] == 'K' || data->facing[x] == 'S')
		&& data->hit[x][0].type == 'K' && data->hit[x][0].distance < 1.2)
		draw_info(data, 'K');
}

void	draw(t_data *data)
{
	int	x;
	int	hit_c;

	x = 0;
	while (x < WIDTH)
	{
		hit_c = 0;
		while (hit_c <= data->hit_count[x])
		{
			if (data->hit[x][hit_c].distance > 0)
			{
				if (data->hit[x][hit_c].type == 'S')
					draw_sprites(data, x, hit_c);
				else
					draw_walls(data, x, hit_c);
			}
			hit_c++;
		}
		if (x == WIDTH / 2)
			check_info(data, x);
		x++;
	}
}
