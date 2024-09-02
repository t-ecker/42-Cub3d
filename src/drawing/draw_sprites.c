/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:44:57 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 00:33:59 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	printf_sprite_lines(t_data *data, double transformY, int x, int hit_c)
{
	int	color;

	while (data->texture->startY < data->texture->endY)
	{
		data->texture->texY = (int)data->texture->tex_pos
			% data->sprites[data->hit[x][hit_c].sprite_t].tex->height;
		data->texture->tex_pos += data->texture->step;
		if (transformY > 0 && transformY
			< data->hit[x][data->hit_count[x]].distance)
		{
			if (is_pixel_transp(data->cubed->walls, x, data->texture->startY))
			{
				color = get_texture_color(
						data->sprites[data->hit[x][hit_c].sprite_t].tex,
						data->texture->texX, data->texture->texY);
				if (color != 0x00000000 && (color & 0xFF) > 200)
					my_put_pixel(data->cubed->walls, x, data->texture->startY,
						add_fog(color, data->weapon, INT_MAX, transformY));
			}
		}
		data->texture->startY++;
	}
}

void	calc_sprite(t_data *data, int hit_c, int x)
{
	int		spritescreen_x;
	double	sprite_x;
	double	sprite_y;
	int		spritewidth;

	sprite_x = data->sprites[data->hit[x][hit_c].sprite_t].x - data->posX;
	sprite_y = data->sprites[data->hit[x][hit_c].sprite_t].y - data->posY;
	data->texture->invdet = 1.0
		/ (data->planeX * data->dirY - data->dirX * data->planeY);
	data->texture->transformX = data->texture->invdet
		* (data->dirY * sprite_x - data->dirX * sprite_y);
	data->texture->transformY = data->texture->invdet
		* (-data->planeY * sprite_x + data->planeX * sprite_y);
	spritescreen_x = (int)((WIDTH / 2)
			* (1 + data->texture->transformX / data->texture->transformY));
	data->texture->height = abs((int)(HEIGHT / data->texture->transformY));
	spritewidth = abs((int)(HEIGHT / data->texture->transformY));
	data->texture->texX = (int)((x - (-spritewidth / 2 + spritescreen_x))
			* data->sprites[data->hit[x][hit_c].sprite_t].tex->width
			/ spritewidth);
}

void	draw_sprites(t_data *data, int x, int hit_c)
{
	if (data->sprites[data->hit[x][hit_c].sprite_t].status != 'D')
	{
		calc_sprite(data, hit_c, x);
		data->texture->startY = -data->texture->height / 2 + HEIGHT / 2;
		if (data->texture->startY < 0)
			data->texture->startY = 0;
		data->texture->endY = data->texture->height / 2 + HEIGHT / 2;
		if (data->texture->endY >= HEIGHT)
			data->texture->endY = HEIGHT - 1;
		data->texture->step = 1.0
			* data->sprites[data->hit[x][hit_c].sprite_t].tex->height
			/ data->texture->height;
		data->texture->tex_pos = (data->texture->startY - HEIGHT
				/ 2 + data->texture->height / 2) * data->texture->step;
		printf_sprite_lines(data, data->texture->transformY, x, hit_c);
	}
}
