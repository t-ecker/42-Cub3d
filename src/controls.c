/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:02:11 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 20:32:31 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void clear_image(mlx_image_t *image)
{
	uint32_t transparent_color = 0x00000000;
    for (uint32_t y = 0; y < image->height; y++)
    {
        for (uint32_t x = 0; x < image->width; x++)
        {
            mlx_put_pixel(image, x, y, transparent_color);
        }
    }
}


void	ft_window_hook(void *param)
{
	mlx_t	*mlx;
	t_data *data;
	double angle;
	double oldDirX;
	double oldDirY;

	angle = 2 * (M_PI / 180);
	
	data = param;
	oldDirX = data->dirX;
	oldDirY = data->dirY;
	mlx = data->cubed->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		data->dirX = cos(angle) * oldDirX - sin(angle) * oldDirY;
		data->dirY = sin(angle) * oldDirX + cos(angle) * oldDirY;
		setPlane(data);
		castRays(data);
		clear_image(data->cubed->walls);
		draw_walls(data->cubed, data);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		data->dirX = cos(angle) * oldDirX + sin(angle) * oldDirY;
		data->dirY = -sin(angle) * oldDirX + cos(angle) * oldDirY;
		
		setPlane(data);
		castRays(data);
		clear_image(data->cubed->walls);
		draw_walls(data->cubed, data);
	}

}

void	ft_hook(t_data *data)
{
	
	mlx_loop_hook(data->cubed->mlx, ft_window_hook, data);
}
