/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:22:07 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 14:48:30 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_overlay_img(t_cubed *cubed, t_input *input, t_data *data)
{
	cubed->overlay = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->overlay
		|| (mlx_image_to_window(cubed->mlx, cubed->overlay, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, cubed, input);
		return (0);
	}
	return (1);
}

int	init_victory_img(t_cubed *cubed, t_input *input, t_data *data)
{
	cubed->victory = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->victory
		|| (mlx_image_to_window(cubed->mlx, cubed->victory, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, cubed, input);
		return (0);
	}
	return (1);
}

int	init_info_img(t_cubed *cubed, t_input *input, t_data *data)
{
	cubed->info = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->info
		|| (mlx_image_to_window(cubed->mlx, cubed->info, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, cubed, input);
		return (0);
	}
	return (1);
}

int	init_walls_img(t_cubed *cubed, t_input *input, t_data *data)
{
	// cubed->walls = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->walls
		|| (mlx_image_to_window(cubed->mlx, cubed->walls, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, cubed, input);
		return (0);
	}
	return (1);
}

int	init_bg_img(t_cubed *cubed, t_input *input, t_data *data)
{
	// cubed->bg = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->bg
		|| (mlx_image_to_window(cubed->mlx, cubed->bg, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, cubed, input);
		return (0);
	}
	return (1);
}

int	init_image(t_input *input, t_cubed *cubed, t_data *data)
{
	cubed->bg = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->walls = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	setPlane(data);
	castRays(data);
	draw_walls(cubed, data);
	ft_hook(data);
	if (!init_bg_img(cubed, input, data))
		return (0);
	ceiling_floor(cubed, input);
	if (!init_walls_img(cubed, input, data))
		return (0);
	if (!init_overlay_img(cubed, input, data))
		return (0);
	if (!init_info_img(cubed, input, data))
		return (0);
	if (!init_victory_img(cubed, input, data))
		return (0);
	mlx_loop(cubed->mlx);
	mlx_terminate(cubed->mlx);
	return (1);
}
