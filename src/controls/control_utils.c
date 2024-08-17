/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/17 14:12:25 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	redraw(t_data *data)
{
		setPlane(data);
		castRays(data);
		clear_image(data->cubed->walls);
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
	if (data->Map[(int)newY][(int)(newX + buffer)] == '1'
		|| data->Map[(int)newY][(int)(newX - buffer)] == '1')
		canmoveX = 0;
	if (data->Map[(int)(newY + buffer)][(int)newX] == '1'
		|| data->Map[(int)(newY - buffer)][(int)newX] == '1')
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
	else
		return ;
	redraw(data);
}
