/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:02:11 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 10:09:01 by tomecker         ###   ########.fr       */
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

void	ft_movement_hook(void *param)
{
	t_data	*data;
	mlx_t	*mlx;
	double	speed;

	data = (t_data *)param;
	speed = 1 / data->speed;
	mlx = data->cubed->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_W)
		&& mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		move_forward(data, speed / 2);
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_forward(data, speed);
	else if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_forward(data, -speed);
	else if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_right(data, speed);
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_right(data, -speed);
}

void	ft_camera_hook(void *param)
{
	t_data	*data;
	double	angle;
	double	olddir_x;
	double	olddir_y;

	angle = 4 * (M_PI / 180);
	data = param;
	olddir_x = data->dirX;
	olddir_y = data->dirY;
	if (mlx_is_key_down(data->cubed->mlx, MLX_KEY_RIGHT))
	{
		data->dirX = cos(angle) * olddir_x - sin(angle) * olddir_y;
		data->dirY = sin(angle) * olddir_x + cos(angle) * olddir_y;
	}
	if (mlx_is_key_down(data->cubed->mlx, MLX_KEY_LEFT))
	{
		data->dirX = cos(angle) * olddir_x + sin(angle) * olddir_y;
		data->dirY = -sin(angle) * olddir_x + cos(angle) * olddir_y;
	}
}

void	ft_gameplay_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = param;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS
		&& ((data->facing[WIDTH / 2] == 'D'
				&& data->Map[(int)(data->posY
					+ data->dirY)][(int)(data->posX + data->dirX)] == 'D')
			|| ((data->facing[WIDTH / 2] == 'K'
			|| data->facing[WIDTH / 2] == 'S')
				&& data->Map[(int)data->posY][(int)data->posX] != 'K'
				&& data->Map[(int)(data->posY + data->dirY)][(int)(data->posX
					+ data->dirX)] == 'K')))
	{
		change_door(data);
	}
	if (key.key == MLX_KEY_F && key.action == MLX_PRESS
		&& data->facing[WIDTH / 2] == 'F')
	{
		data->end = 1;
		clear_image(data->cubed->hand);
		draw_overlay_part(data->cubed->victory, data->texture->victory, 0, 0);
	}
}

void	ft_window_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(data->cubed->mlx);
	if (key.key == MLX_KEY_1 && key.action == MLX_PRESS)
		change_weapon(data, 1);
	else if (key.key == MLX_KEY_2 && key.action == MLX_PRESS)
		change_weapon(data, 2);
	if (data->weapon == 1)
		ft_light_hook(key, param);
	// else if (data->weapon == 2)
	// 	ft_shoot_hook(key, param);
	ft_gameplay_hook(key, param);
}
