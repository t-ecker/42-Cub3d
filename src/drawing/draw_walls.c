/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:26:38 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/17 12:10:44 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	my_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
		mlx_put_pixel(img, x, y, color);
}

int get_color(char hit_side)
{
    if (hit_side == 'n')
        return (0xE6E6FAFF);
    if (hit_side == 's')
        return (0xF08080FF);
    if (hit_side == 'w')
        return (0x90EE90FF);
    if (hit_side == 'e')
        return (0xFFC0CBFF);
    return (0);
}

void	draw_walls(t_cubed *cubed, t_data *data)
{
	int x;
	int y;
	int height;
	int startY;
	int endY;

	x = 0;
	while (x < WIDTH)
	{
		height = HEIGHT / data->wallDistances[x];
		startY = -height / 2 + HEIGHT / 2;
		endY = height / 2 + HEIGHT / 2;
		y = startY;
		while(y < endY)
		{
        	my_put_pixel(cubed->walls, x, y, get_color(data->hit_side[x]));
			y++;
		}

		x++;
	}
}
