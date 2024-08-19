/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:50:36 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/20 01:22:23 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	ft_shoot_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_REPEAT)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->recoil);
		mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
			(WIDTH - data->cubed->hand->width) - 200,
			HEIGHT - data->cubed->hand->height);
	}
	else if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		data->cubed->hand = mlx_texture_to_image(data->cubed->mlx,
				data->texture->shoot);
		mlx_image_to_window(data->cubed->mlx, data->cubed->hand,
			(WIDTH - data->cubed->hand->width) - 200,
			HEIGHT - data->cubed->hand->height);
	}
	else if (key.key == MLX_KEY_SPACE && key.action == MLX_RELEASE)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		draw_hand(data);
	}
}

void	ft_light_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_REPEAT)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->light);
		data->cubed->light = mlx_texture_to_image(data->cubed->mlx,
				data->texture->light);
		mlx_image_to_window(data->cubed->mlx, data->cubed->light, 0, 0);
	}
	else if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->light);
		data->cubed->light = mlx_texture_to_image(data->cubed->mlx,
				data->texture->light);
		mlx_image_to_window(data->cubed->mlx, data->cubed->light, 0, 0);
	}
	else if (key.key == MLX_KEY_SPACE && key.action == MLX_RELEASE)
	{
		ft_dark_img(data->cubed->light);
	}
	mlx_delete_image(data->cubed->mlx, data->cubed->hand);
	draw_hand(data);
}
