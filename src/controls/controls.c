/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:02:11 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 00:24:04 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void movement(t_data *data, mlx_t *mlx)
{
	double	newX;
	double	newY;

	newX = data->posX;
	newY = data->posY;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		newX += data->dirX / 20;
		newY += data->dirY / 20;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		newX -= data->dirX / 20;
		newY -= data->dirY / 20;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		newX += data->planeX / 20;
		newY += data->planeY / 20;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		newX -= data->planeX / 20;
		newY -= data->planeY / 20;
	}
	collision(data, newX, newY);
}

void ft_camera_hook(void *param)
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
		redraw(data);
	}
	if (mlx_is_key_down(data->cubed->mlx, MLX_KEY_LEFT))
	{
		data->dirX = cos(angle) * oldDirX + sin(angle) * oldDirY;
		data->dirY = -sin(angle) * oldDirX + cos(angle) * oldDirY;
		redraw(data);
	}
}

void ft_window_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->cubed->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->cubed->mlx);
	movement(data, data->cubed->mlx);
}

void ft_hook(t_data *data)
{
	mlx_loop_hook(data->cubed->mlx, ft_window_hook, data);
	mlx_loop_hook(data->cubed->mlx, ft_camera_hook, data);
}
