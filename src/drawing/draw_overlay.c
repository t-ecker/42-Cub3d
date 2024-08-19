/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_overlay.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:15:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 07:12:56 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	draw_overlay_part(mlx_image_t *img, mlx_texture_t *texture, int dst_x, int dst_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)texture->height)
	{
		x = 0;
		while (x < (int)texture->width)
		{
			my_put_pixel(img, dst_x + x, dst_y + y, get_texture_color(texture, x, y));
			x++;
		}
		y++;
	}
}

void	ft_shoot_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_REPEAT)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->recoil);
		mlx_resize_image(data->cubed->hand, 300, 300);
		mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
			(WIDTH - data->cubed->hand->width) - 200,
			HEIGHT - data->cubed->hand->height);
	}
	if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->shoot);
		mlx_resize_image(data->cubed->hand, 300, 300);
		mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
			(WIDTH - data->cubed->hand->width) - 200,
			HEIGHT - data->cubed->hand->height);
	}
	if (key.key == MLX_KEY_SPACE && key.action == MLX_RELEASE)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->hand);
		mlx_resize_image(data->cubed->hand, 300, 300);
		mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
			(WIDTH - data->cubed->hand->width) - 200,
			HEIGHT - data->cubed->hand->height);
	}
}

void	draw_overlay(t_data *data)
{
	mlx_texture_t	*crosshair;

	crosshair = mlx_load_png("./assets/crosshair_1.PNG");
	draw_overlay_part(data->cubed->overlay, crosshair,
		(WIDTH - crosshair->width) / 2, HEIGHT / 2);
	data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
			data->texture->hand);
	mlx_resize_image(data->cubed->hand, 300, 300);
	mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
		(WIDTH - data->cubed->hand->height) - 200,
		HEIGHT - data->cubed->hand->height);
}
