/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:43:10 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 18:49:04 by tomecker         ###   ########.fr       */
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
