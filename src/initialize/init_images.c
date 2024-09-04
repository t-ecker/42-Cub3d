/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:22:07 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 17:05:03 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_walls_img(t_cubed *cubed, t_input *input, t_data *data)
{
	cubed->walls = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
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
	cubed->bg = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	if (!cubed->bg
		|| (mlx_image_to_window(cubed->mlx, cubed->bg, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, cubed, input);
		return (0);
	}
	draw_bg(data, input);
	return (1);
}
