/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:50:36 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 18:04:59 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

// void	ft_shoot_hook(struct mlx_key_data key, void *param)
// {
// 	t_data	*data;

// 	data = (t_data *)param;
// 	if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
// 	{
// 		clear_image(data->cubed->hand);
// 		draw_overlay_part(data->cubed->hand, data->texture->shoot, 0, 0);
// 	}
// 	else if (key.key == MLX_KEY_SPACE && key.action == MLX_REPEAT)
// 	{
// 		clear_image(data->cubed->hand);
// 		draw_overlay_part(data->cubed->hand, data->texture->recoil, 0, 0);
// 	}
// 	else if (key.key == MLX_KEY_SPACE && key.action == MLX_RELEASE)
// 	{
// 		clear_image(data->cubed->hand);
// 		draw_overlay_part(data->cubed->hand, data->texture->hand, 0, 0);
// 	}
// }

void	ft_light_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_PRESS)
	{
		if (data->toggle_light == 0)
			data->toggle_light = 1;
		else
			data->toggle_light = 0;
	}
	if (data->toggle_light)
	{
		draw_overlay_part(data->cubed->light, data->texture->light, 0, 0);
	}
	else if (!data->toggle_light)
		ft_dark_img(data->cubed->light);
	clear_image(data->cubed->hand);
	draw_overlay_part(data->cubed->hand, data->texture->flashlight,
		0, 0);
}

