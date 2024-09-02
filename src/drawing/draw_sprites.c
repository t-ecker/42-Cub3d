/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:44:57 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/02 22:45:33 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void draw_sprites(t_data *data, int x, int hit_c)
{
	if (data->sprites[data->hit[x][hit_c].sprite_t].status != 'D')
	{
		double spriteX = data->sprites[data->hit[x][hit_c].sprite_t].x - data->posX;
		double spriteY = data->sprites[data->hit[x][hit_c].sprite_t].y - data->posY;

		double invDet = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY);

		double transformX = invDet * (data->dirY * spriteX - data->dirX * spriteY);
		double transformY = invDet * (-data->planeY * spriteX + data->planeX * spriteY);

		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

		int height = abs((int)(HEIGHT / transformY));
		int spriteWidth = abs((int)(HEIGHT / transformY));

		int startY = -height / 2 + HEIGHT / 2;
		if (startY < 0)
			startY = 0;
		int endY = height / 2 + HEIGHT / 2;
		if (endY >= HEIGHT)
			endY = HEIGHT - 1;

		int texX = (int)((x - (-spriteWidth / 2 + spriteScreenX)) * data->sprites[data->hit[x][hit_c].sprite_t].tex->width / spriteWidth);

		data->texture->step = 1.0 * data->sprites[data->hit[x][hit_c].sprite_t].tex->height / height;
		data->texture->tex_pos = (startY - HEIGHT / 2 + height / 2) * data->texture->step;

		while (startY < endY)
		{
			data->texture->texY = (int)data->texture->tex_pos % data->sprites[data->hit[x][hit_c].sprite_t].tex->height;
			data->texture->tex_pos += data->texture->step;

			if (transformY > 0 && transformY < data->hit[x][data->hit_count[x]].distance)
			{
				if (is_pixel_transp(data->cubed->walls, x, startY))
				{
					int color = get_texture_color(data->sprites[data->hit[x][hit_c].sprite_t].tex, texX, data->texture->texY);
					if (color != 0x00000000 && (color & 0xFF) > 200)
						my_put_pixel(data->cubed->walls, x, startY, add_fog(color, data->weapon, INT_MAX, transformY));
				}
			}
			startY++;
		}
	}
}