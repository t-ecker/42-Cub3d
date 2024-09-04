/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:44:57 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 13:14:42 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	printf_sprite_lines(t_data *data, double transform_y, int x, int hit_c)
{
	int	color;

	while (data->texture->start_y < data->texture->end_y)
	{
		data->texture->tex_y = (int)data->texture->tex_pos
			% data->sprites[data->hit[x][hit_c].sprite_t].tex->height;
		data->texture->tex_pos += data->texture->step;
		if (transform_y > 0 && transform_y
			< data->hit[x][data->hit_count[x]].distance)
		{
			if (is_pixel_transp(data->cubed->walls, x, data->texture->start_y))
			{
				color = get_texture_color(
						data->sprites[data->hit[x][hit_c].sprite_t].tex,
						data->texture->tex_x, data->texture->tex_y);
				if (color != 0x00000000 && (color & 0xFF) > 200)
					my_put_pixel(data->cubed->walls, x, data->texture->start_y,
						add_fog(color, data->weapon, INT_MAX, transform_y));
			}
		}
		data->texture->start_y++;
	}
}

void	calc_sprite(t_data *data, int hit_c, int x)
{
	int		spritescreen_x;
	double	sprite_x;
	double	sprite_y;
	int		spritewidth;

	sprite_x = data->sprites[data->hit[x][hit_c].sprite_t].x - data->pos_x;
	sprite_y = data->sprites[data->hit[x][hit_c].sprite_t].y - data->pos_y;
	data->texture->invdet = 1.0
		/ (data->plane_x * data->dir_y - data->dir_x * data->plane_y);
	data->texture->transform_x = data->texture->invdet
		* (data->dir_y * sprite_x - data->dir_x * sprite_y);
	data->texture->transform_y = data->texture->invdet
		* (-data->plane_y * sprite_x + data->plane_x * sprite_y);
	spritescreen_x = (int)((WIDTH / 2)
			* (1 + data->texture->transform_x / data->texture->transform_y));
	data->texture->height = abs((int)(HEIGHT / data->texture->transform_y));
	spritewidth = abs((int)(HEIGHT / data->texture->transform_y));
	data->texture->tex_x = (int)((x - (-spritewidth / 2 + spritescreen_x))
			* data->sprites[data->hit[x][hit_c].sprite_t].tex->width
			/ spritewidth);
}

void	draw_sprites(t_data *data, int x, int hit_c)
{
	if (data->sprites[data->hit[x][hit_c].sprite_t].status != 'D')
	{
		calc_sprite(data, hit_c, x);
		data->texture->start_y = -data->texture->height / 2 + HEIGHT / 2;
		if (data->texture->start_y < 0)
			data->texture->start_y = 0;
		data->texture->end_y = data->texture->height / 2 + HEIGHT / 2;
		if (data->texture->end_y >= HEIGHT)
			data->texture->end_y = HEIGHT - 1;
		data->texture->step = 1.0
			* data->sprites[data->hit[x][hit_c].sprite_t].tex->height
			/ data->texture->height;
		data->texture->tex_pos = (data->texture->start_y - HEIGHT
				/ 2 + data->texture->height / 2) * data->texture->step;
		printf_sprite_lines(data, data->texture->transform_y, x, hit_c);
	}
}
