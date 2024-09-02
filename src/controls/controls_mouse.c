/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:46:18 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 17:23:32 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

double	get_angle(int cursorx)
{
	double	sensitivity;
	int		screen_center_x;
	double	angle;

	screen_center_x = WIDTH / 2;
	sensitivity = 0.0020;
	angle = (cursorx - screen_center_x) * sensitivity;
	return (angle);
}

void	center_mouse(void *param)
{
	int		screen_center_x;
	int		screen_center_y;
	t_data	*data;

	data = param;
	screen_center_x = WIDTH / 2;
	screen_center_y = HEIGHT / 2;
	mlx_set_mouse_pos(data->cubed->mlx, screen_center_x, screen_center_y);
}

void	ft_cursor_camera_hook(void *param)
{
	int		cursorx;
	int		cursory;
	double	old_dir_x;
	double	old_dir_y;
	t_data	*data;

	data = param;
	mlx_get_mouse_pos(data->cubed->mlx, &cursorx, &cursory);
	old_dir_x = data->dirX;
	old_dir_y = data->dirY;
	data->dirX = cos(get_angle(cursorx)) * old_dir_x
		- sin(get_angle(cursorx)) * old_dir_y;
	data->dirY = sin(get_angle(cursorx)) * old_dir_x
		+ cos(get_angle(cursorx)) * old_dir_y;
	center_mouse(param);
}

int	get_sprite(t_data *data)
{
	int i;

	i = 0;
	while (data->hit[WIDTH / 2][i].type == 'K')
		i++;
	return (i);
}

void	ft_mouse_shoot_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_data	*data;
	t_sprite *sprite;

	data = (t_data *)param;
	(void)mods;
	if (data->weapon == 2)
	{
		sprite = &data->sprites[data->hit[WIDTH / 2][get_sprite(data)].sprite_t];
		if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		{
			clear_image(data->cubed->hand);
			draw_overlay_part(data->cubed->hand, data->texture->shoot, 0, 0);
			if (data->facing[WIDTH / 2] == 'S' && sprite->status == 'A')
			{
				sprite->tex = data->texture->monster_s;
				sprite->status = 'S';

			}
			else if (data->facing[WIDTH / 2] == 'S' && sprite->status == 'S')
			{
				data->Map[(int)sprite->y][(int)sprite->x] = '0';
				sprite->status = 'D';
			}
		}
		else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		{
			clear_image(data->cubed->hand);
			draw_overlay_part(data->cubed->hand, data->texture->hand, 0, 0);
		}
	}
}
