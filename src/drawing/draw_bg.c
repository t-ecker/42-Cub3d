/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:06:15 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 14:50:52 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	ceiling_floor(t_cubed *cubed, t_input *input)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			mlx_put_pixel((*cubed).bg, j, i, input->ceiling);
	}
	i--;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			mlx_put_pixel((*cubed).bg, j, i, input->floor);
	}
}

void	draw_bg(mlx_image_t *img, int color)
{
	int x;
	int y;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			my_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
