/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:02:11 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 17:14:49 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	ft_movement_hook(void *param)
{
	double	newX;
	double	newY;
	mlx_t	*mlx;
	t_data	*data;

	data = (t_data *)param;
	mlx = data->cubed->mlx;
	newX = data->posX;
	newY = data->posY;
	if (mlx_is_key_down(mlx, MLX_KEY_W) && mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
	{
		newX += data->dirX / 10;
		newY += data->dirY / 10;
		collision(data, newX, newY);
	}
	else if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		newX += data->dirX / 20;
		newY += data->dirY / 20;
		collision(data, newX, newY);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		newX -= data->dirX / 20;
		newY -= data->dirY / 20;
		collision(data, newX, newY);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		newX += data->planeX / 20;
		newY += data->planeY / 20;
		collision(data, newX, newY);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		newX -= data->planeX / 20;
		newY -= data->planeY / 20;
		collision(data, newX, newY);
	}
}

void	ft_camera_hook(void *param)
{
	t_data	*data;
	double	angle;
	double	oldDirX;
	double	oldDirY;

	angle = 2 * (M_PI / 180);
	data = param;
	oldDirX = data->dirX;
	oldDirY = data->dirY;
	if (mlx_is_key_down(data->cubed->mlx, MLX_KEY_RIGHT))
	{
		data->dirX = cos(angle) * oldDirX - sin(angle) * oldDirY;
		data->dirY = sin(angle) * oldDirX + cos(angle) * oldDirY;
	}
	if (mlx_is_key_down(data->cubed->mlx, MLX_KEY_LEFT))
	{
		data->dirX = cos(angle) * oldDirX + sin(angle) * oldDirY;
		data->dirY = -sin(angle) * oldDirX + cos(angle) * oldDirY;
	}
}

void	ft_window_hook(struct mlx_key_data key, void *param)
{
	t_data	*data;

	data = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(data->cubed->mlx);
	if (key.key == MLX_KEY_1 && key.action == MLX_PRESS)
	{
		ft_dark_img(data->cubed->light);
		data->weapon = 1;
	}
	else if (key.key == MLX_KEY_2 && key.action == MLX_PRESS)
	{
		data->weapon = 2;
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		draw_hand(data);
	}
	if (data->weapon == 1)
	{
		mlx_delete_image(data->cubed->mlx, data->cubed->hand);
		draw_hand(data);
		ft_light_hook(key, param);
	}
	else if (data->weapon == 2)
	{
		clear_image(data->cubed->light);
		ft_shoot_hook(key, param);
	}
}

void	ft_hook(t_data *data)
{
	mlx_loop_hook(data->cubed->mlx, ft_camera_hook, data);
	mlx_loop_hook(data->cubed->mlx, ft_movement_hook, data);
	mlx_key_hook(data->cubed->mlx, ft_window_hook, data);
}
