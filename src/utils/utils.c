/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 02:09:50 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 01:28:35 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	clamp(int value)
{
	if (value < 0)
		return (-1);
	if (value > 255)
		return (-1);
	return (value);
}

void	remove_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	rgb_to_rgba_hex(int r, int g, int b, int a)
{
	int	rgba;

	r = clamp(r);
	g = clamp(g);
	b = clamp(b);
	a = clamp(a);
	printf("%d, %d, %d, %d\n", r, g, b, a);
	if (r == -1 || g == -1 || b == -1 || a == -1)
		return (0);
	rgba = (r << 24) | (g << 16) | (b << 8) | a;
	printf("%X\n", rgba);
	return (rgba);
}

void	clear_image(mlx_image_t *image)
{
	uint32_t transparent_color;
	uint32_t y;
	uint32_t x;

	y = 0;
	transparent_color = 0x00000000;
    while(y < image->height)
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
