/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_overlay.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:15:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 03:11:05 by dolifero         ###   ########.fr       */
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

// void	shoot_hook(void *param)
// {
// 	t_data	*data;
// 	mlx_texture_t	*shoot;
// 	mlx_texture_t	*recoil;
// 	mlx_texture_t	*hand;
// 	mlx_image_t		*hand_img;

// 	data = (t_data *)param;
// 	shoot = mlx_load_png("./assets/pistol_shoot.png");
// 	hand_img = mlx_texture_to_image(data->cubed->mlx, hand);
// 	mlx_image_to_window(data->cubed->mlx, hand_img, (WIDTH - hand_img->width) - 200, HEIGHT - hand_img->height);
// }

void	draw_overlay(t_data *data)
{
	mlx_texture_t	*crosshair;
	mlx_texture_t	*hand;
	mlx_image_t		*hand_img;

	crosshair = mlx_load_png("./assets/crosshair_1.PNG");
	draw_overlay_part(data->cubed->overlay, crosshair,
		(WIDTH - crosshair->width) / 2, HEIGHT / 2);
	hand = mlx_load_png("./assets/pistol_static.png");
	hand_img = mlx_texture_to_image(data->cubed->mlx, hand);
	mlx_resize_image(hand_img, 300, 300);
	mlx_image_to_window(data->cubed->mlx, hand_img,
		(WIDTH - hand_img->width) - 200, HEIGHT - hand_img->height);
	// mlx_loop_hook(data->cubed->mlx, shoot_hook, data);
}
