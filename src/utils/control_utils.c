/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 15:38:55 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	move_forward(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->dir_x / speed;
	new_y = data->pos_y + data->dir_y / speed;
	collision(data, new_x, new_y);
}

void	move_right(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->plane_x / speed;
	new_y = data->pos_y + data->plane_y / speed;
	collision(data, new_x, new_y);
}

void	change_weapon(t_data *data, int weapon)
{
	data->weapon = weapon;
	if (weapon == 1)
	{
		ft_dark_img(data->cubed->light);
		clear_image(data->cubed->minimap);
		data->minimap = 0;
	}
	else
	{
		data->minimap = 1;
		ft_draw_minimap(data);
		clear_image(data->cubed->light);
	}
	clear_image(data->cubed->bg);
	draw_bg(data, data->input);
	clear_image(data->cubed->hand);
	draw_overlay_part(data->cubed->hand, data->texture->hand,
		0, 0);
}

void	change_door(t_data *data)
{
	if (data->map[(int)(data->pos_y + data->dir_y)][(int)(data->pos_x
			+ data->dir_x)] == 'D')
		data->map[(int)(data->pos_y + data->dir_y)][(int)(data->pos_x
				+ data->dir_x)] = 'K';
	else if (data->map[(int)(data->pos_y + data->dir_y)][(int)(data->pos_x
			+ data->dir_x)] == 'K')
		data->map[(int)(data->pos_y + data->dir_y)][(int)(data->pos_x
				+ data->dir_x)] = 'D';
}

void	check_minimap(struct mlx_key_data key, t_data *data)
{
	if (key.key == MLX_KEY_M && key.action == MLX_PRESS)
	{
		if (data->minimap)
		{
			data->minimap = 0;
			clear_image(data->cubed->minimap);
		}
		else
		{
			data->minimap = 1;
			ft_draw_minimap(data);
		}
	}
}
