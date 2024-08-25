/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 01:46:18 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/25 02:41:37 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void get_angle(double *angle, int cursorx)
{
	if (cursorx > WIDTH / 2 + 100)
		*angle = 6 * (M_PI / 180);
	else if (cursorx < WIDTH / 2 - 100)
		*angle = 6 * (M_PI / 180);
	else if (cursorx > WIDTH / 2 + 50)
		*angle = 5 * (M_PI / 180);
	else if (cursorx < WIDTH / 2 - 50)
		*angle = 5 * (M_PI / 180);
	else
		*angle = 4 * (M_PI / 180);
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

void ft_cursor_camera_hook(void *param)
{
	int cursorx, cursory;
	int screen_center_x = WIDTH / 2;
	// int screen_center_y = HEIGHT / 2;
	double sensitivity = 0.0005;  // Adjust this to control rotation speed
	double angle;
	double oldDirX;
	double oldDirY;
	t_data *data;

	data = param;
	mlx_get_mouse_pos(data->cubed->mlx, &cursorx, &cursory);
	angle = (cursorx - screen_center_x) * sensitivity;
	oldDirX = data->dirX;
	oldDirY = data->dirY;
	data->dirX = cos(angle) * oldDirX - sin(angle) * oldDirY;
	data->dirY = sin(angle) * oldDirX + cos(angle) * oldDirY;
}
