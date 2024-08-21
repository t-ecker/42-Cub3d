/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:38 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/21 10:11:49 by tomecker         ###   ########.fr       */
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

	if (data->ttu[x] != '0')
	{
		if (data->ttu[x] == 'K')
			texture = data->texture->DO;
		if (data->ttu[x] == 'F')
			texture = data->texture->F;
		if (data->ttu[x] == 'D')
			texture = data->texture->D;
		return (texture);
	}
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

void	draw_over(t_data *data, int x)
{
	int height;
	int startY;
	int endY;

	if (data->wallDistances[x] == 0.0)
		return ;
	height = HEIGHT / data->wallDistances[x];
	startY = -height / 2 + HEIGHT / 2;
	endY = height / 2 + HEIGHT / 2;

	if (startY < 0)
		startY = 0;
	if (endY >= HEIGHT)
		endY = HEIGHT - 1;
	
	mlx_texture_t *texture = get_texture(data, x);
	data->texture->step = 1.0 * texture->height / height;
	data->texture->tex_pos = (startY - HEIGHT / 2 + height / 2) * data->texture->step;
	
	while(startY < endY)
	{
		data->texture->texY = (int)data->texture->tex_pos % texture->height;
		data->texture->tex_pos += data->texture->step;

		int color = get_texture_color(texture, data->texX[x], data->texture->texY);
		if (color != 0x00000000)
			my_put_pixel(data->cubed->walls, x, startY, color);
		startY++;
	}
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
		if (startY < 0)
			startY = 0;
		endY = height / 2 + HEIGHT / 2;
		if (endY >= HEIGHT)
			endY = HEIGHT - 1;
		
		mlx_texture_t *texture = get_texture(data, x);
        data->texture->step = 1.0 * texture->height / height;
        data->texture->tex_pos = (startY - HEIGHT / 2 + height / 2) * data->texture->step;
		if (x == WIDTH / 2)
		{
			if (data->facing[x] == 'F' && data->wallDistances[x] < 1.2)
				draw_info(data, 0);
			if ((data->facing[x] == 'D' && data->cdoor[x] < 1.0))
				draw_info(data, 1);
			if (data->facing[x] == 'K' && data->cdoor[x] < 1.0)
				draw_info(data, 2);
		}
		
		while(startY < endY)
		{
			data->texture->texY = (int)data->texture->tex_pos % texture->height;
			data->texture->tex_pos += data->texture->step;
        	my_put_pixel(cubed->walls, x, startY, get_texture_color(texture, data->texX[x], data->texture->texY));
			startY++;
		}
		if (data->cdoor[x] > 0.0)
		{
			cast_one_ray(data, "KD", x);
			draw_over(data, x);
		}
		x++;
	}
}
