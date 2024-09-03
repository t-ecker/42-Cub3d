/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:43:10 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 10:15:30 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	my_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
		mlx_put_pixel(img, x, y, color);
}

int	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	int		index;
	t_color	color;

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

int	is_pixel_transp(mlx_image_t *image, int x, int y)
{
	uint8_t	*pixel;
	uint8_t	alpha;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return (0);
	pixel = &image->pixels[(y * image->width + x) * 4];
	alpha = pixel[3];
	if (alpha == 0)
		return (1);
	return (0);
}

int	add_fog(int color, int fog, double fog_factor, double distance)
{
	t_color	after;

	if (fog == 2)
		return (color);
	if (fog_factor == INT_MAX)
		fog_factor = (distance - 1) / (3.5 - 1);
	if (fog_factor < 0)
		fog_factor = 0;
	if (fog_factor > 1)
		fog_factor = 1;
	after.a = color & 0xFF;
	after.r = (int)((1.0 - fog_factor) * ((color >> 24) & 0xFF));
	after.g = (int)((1.0 - fog_factor) * ((color >> 16) & 0xFF));
	after.b = (int)((1.0 - fog_factor) * ((color >> 8) & 0xFF));
	return ((after.r << 24) | (after.g << 16) | (after.b << 8) | after.a);
}

void	clear_image(mlx_image_t *image)
{
	uint32_t	transparent_color;
	uint32_t	y;
	uint32_t	x;

	y = 0;
	transparent_color = 0x00000000;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel(image, x, y, transparent_color);
			x++;
		}
		y++;
	}
}
