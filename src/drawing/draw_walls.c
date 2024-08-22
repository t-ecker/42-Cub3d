/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:38 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/22 12:55:54 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	print_mapp(t_data *data)
{
	int	i;

	i = 0;
	while (data->Map[i])
	{
		printf("%s\n", data->Map[i]);
		i++;
	}
	printf("\n");
}

void	redraw(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	setPlane(data);
	castRays(data);
	clear_image(data->cubed->walls);
  	clear_image(data->cubed->info);
	draw_walls(data->cubed, data);
}

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

int is_pixel_transp(mlx_image_t* image, int x, int y)
{
	uint8_t* pixel;
	uint8_t alpha;

    if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
        return (0);
    pixel = &image->pixels[(y * image->width + x) * 4];
    alpha = pixel[3];
    if (alpha == 0)
        return (1);
    return (0);
}

void	draw_walls(t_cubed *cubed, t_data *data)
{
	int x;
	int height;
	int startY;
	int endY;
	int hit_c;

	x = 0;
	height = 0;
	while (x < WIDTH)
	{
		hit_c = 0;
		while (hit_c <= data->hit_count[x])
		{
			if (data->hit[x][hit_c].distance > 0)
			{
				height = HEIGHT / data->hit[x][hit_c].distance;
				startY = -height / 2 + HEIGHT / 2;
				if (startY < 0)
					startY = 0;
				endY = height / 2 + HEIGHT / 2;
				if (endY >= HEIGHT)
					endY = HEIGHT - 1;
					
				mlx_texture_t *texture = data->hit[x][hit_c].tex;
				data->texture->step = 1.0 * texture->height / height;
				data->texture->tex_pos = (startY - HEIGHT / 2 + height / 2) * data->texture->step;
				
				while(startY < endY)
				{
					if (is_pixel_transp(data->cubed->walls, x, startY))
					{
						data->texture->texY = (int)data->texture->tex_pos % texture->height;
						data->texture->tex_pos += data->texture->step;
						int color = get_texture_color(texture, data->hit[x][hit_c].texX, data->texture->texY);
						if (color != 0x00000000)
							my_put_pixel(cubed->walls, x, startY, color);	
					}
					startY++;
				}
			}
			hit_c++;
		}
		if (x == WIDTH / 2)
		{
			if (data->facing[x] == 'F' && data->hit[x][0].type == 'F' && data->hit[x][0].distance < 1.2)
				draw_info(data, 'F');
			if ((data->facing[x] == 'D' && data->hit[x][0].type == 'D' && data->hit[x][0].distance < 1.2))
				draw_info(data, 'D');
			if (data->facing[x] == 'K' && data->hit[x][0].type == 'K' && data->hit[x][0].distance < 1.2)
				draw_info(data, 'K');
		}
		x++;
	}
}
