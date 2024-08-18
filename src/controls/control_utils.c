/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 14:38:29 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void redraw(t_data *data)
{
	setPlane(data);
	castRays(data);
	clear_image(data->cubed->walls);
	clear_image(data->cubed->info);
	draw_walls(data->cubed, data);
}

void	collision(t_data *data, double newX, double newY)
{
	float	buffer;
	int		canmoveX;
	int		canmoveY;

	canmoveX = 1;
	canmoveY = 1;
	buffer = 0.3;
    if ((data->Map[(int)data->posY][(int)(newX + buffer)] == '1' && newX > data->posX) ||
        (data->Map[(int)data->posY][(int)(newX - buffer)] == '1' && newX < data->posX))
        canmoveX = 0;

    if ((data->Map[(int)(newY + buffer)][(int)data->posX] == '1' && newY > data->posY) ||
        (data->Map[(int)(newY - buffer)][(int)data->posX] == '1' && newY < data->posY))
        canmoveY = 0;
	if (canmoveX && canmoveY)
	{
		data->posX = newX;
		data->posY = newY;
	}
	else if (canmoveX)
		data->posX = newX;
	else if (canmoveY)
		data->posY = newY;
	redraw(data);
}
