/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 09:54:28 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	move_forward(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	new_x = data->posX + data->dirX / speed;
	new_y = data->posY + data->dirY / speed;
	collision(data, new_x, new_y);
}

void	move_right(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	new_x = data->posX + data->planeX / speed;
	new_y = data->posY + data->planeY / speed;
	collision(data, new_x, new_y);
}

void	change_weapon(t_data *data, int weapon)
{
	data->weapon = weapon;
	if (weapon == 1)
		ft_dark_img(data->cubed->light);
	else
		clear_image(data->cubed->light);
	clear_image(data->cubed->bg);
	draw_bg(data, data->input);
	clear_image(data->cubed->hand);
	draw_overlay_part(data->cubed->hand, data->texture->hand,
		0, 0);
}

void	change_door(t_data *data)
{
	if (data->Map[(int)(data->posY + data->dirY)][(int)(data->posX
			+ data->dirX)] == 'D')
		data->Map[(int)(data->posY + data->dirY)][(int)(data->posX
				+ data->dirX)] = 'K';
	else if (data->Map[(int)(data->posY + data->dirY)][(int)(data->posX
			+ data->dirX)] == 'K')
		data->Map[(int)(data->posY + data->dirY)][(int)(data->posX
				+ data->dirX)] = 'D';
}
