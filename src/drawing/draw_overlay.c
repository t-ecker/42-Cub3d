/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_overlay.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:15:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 00:30:17 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	draw_overlay_part(mlx_image_t *img, mlx_texture_t *texture,
		int dst_x, int dst_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)texture->height)
	{
		x = 0;
		while (x < (int)texture->width)
		{
			my_put_pixel(img, dst_x + x, dst_y + y,
				get_texture_color(texture, x, y));
			x++;
		}
		y++;
	}
}

void	draw_hand(t_data *data)
{
	if (data->weapon == 1)
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->flashlight);
	else if (data->weapon == 2)
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->hand);
	mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
		(WIDTH - data->cubed->hand->height) - 200,
		HEIGHT - data->cubed->hand->height);
}

void	draw_overlay(t_data *data)
{
	mlx_texture_t	*crosshair;

	crosshair = mlx_load_png("./assets/crosshair_1.PNG");
	draw_overlay_part(data->cubed->overlay, crosshair,
		(WIDTH - crosshair->width) / 2, HEIGHT / 2);
	data->cubed->light = mlx_texture_to_image(data->cubed->mlx,
			data->texture->dark);
	mlx_image_to_window(data->cubed->mlx, data->cubed->light, 0, 0);
	draw_hand(data);
}

void	draw_info(t_data *data, char flag)
{
	if (flag == 'F')
		draw_overlay_part(data->cubed->info, data->texture->infoF,
			(WIDTH - data->texture->infoF->width) / 2, 20);
	else if (flag == 'D')
		draw_overlay_part(data->cubed->info, data->texture->infoD,
			(WIDTH - data->texture->infoD->width) / 2, 20);
	else if (flag == 'K')
		draw_overlay_part(data->cubed->info, data->texture->infoDC,
			(WIDTH - data->texture->infoDC->width) / 2, 20);
}
