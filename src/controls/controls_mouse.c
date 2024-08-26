/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:46:18 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/26 22:07:18 by dolifero         ###   ########.fr       */
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
