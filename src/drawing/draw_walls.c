/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:38 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 18:58:20 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	my_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
		mlx_put_pixel(img, x, y, color);
}

int get_texture_color(mlx_texture_t *texture, int x, int y)
{
	int index;
	t_color color;

    if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
        return (0);
    index = (y * texture->width + x) * 4;    
    color.r = texture->pixels[index];
    color.g = texture->pixels[index + 1];
    color.b = texture->pixels[index + 2];
    color.a = texture->pixels[index + 3];
    color.final = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
    return (color.final);
}


mlx_texture_t *get_texture(t_data *data, int x)
{
	mlx_texture_t *texture;

	if (data->hit_side[x] == 'F')
		texture = data->texture->F;
	if (data->hit_side[x] == 'D')
		texture = data->texture->D;
    if (data->hit_side[x] == 'n')
		texture = data->texture->n;
    if (data->hit_side[x] == 's')
		texture = data->texture->s;
    if (data->hit_side[x] == 'w')
		texture = data->texture->w;
    if (data->hit_side[x] == 'e')
		texture = data->texture->e;
    return (texture);
}

void	draw_walls(t_cubed *cubed, t_data *data)
{
	int x;
	int height;
	int startY;
	int endY;

	x = 0;
	while (x < WIDTH)
	{
		height = HEIGHT / data->wallDistances[x];
		startY = -height / 2 + HEIGHT / 2;
		endY = height / 2 + HEIGHT / 2;
		
		mlx_texture_t *texture = get_texture(data, x);
        data->texture->step = 1.0 * textureH / height;
        data->texture->tex_pos = (startY - HEIGHT / 2 + height / 2) * data->texture->step;

		if (x == WIDTH / 2)
		{
			if (data->facing[x] == 'F' && data->wallDistances[x] < 1.2)
				draw_info(data, 0);
			if (data->facing[x] == 'D' && data->wallDistances[x] < 1.0)
				draw_info(data, 1);
		}
		
		while(startY < endY)
		{
			data->texture->texY = (int)data->texture->tex_pos % textureH;
			data->texture->tex_pos += data->texture->step;
        	my_put_pixel(cubed->walls, x, startY, get_texture_color(texture, data->texX[x], data->texture->texY));
			startY++;
		}
		x++;
	}
}
