/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 00:54:26 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	collision(t_data *data, double newX, double newY)
{
	float	buffer;
	int		canmoveX;
	int		canmoveY;

	canmoveX = 1;
	canmoveY = 1;
	buffer = 0.1;
	if ((newX > data->posX && data->Map[(int)data->posY][(int)(newX + buffer)] == '1') ||
		(newX < data->posX && data->Map[(int)data->posY][(int)(newX - buffer)] == '1'))
		canmoveX = 0;
	if ((newY > data->posY && data->Map[(int)(newY + buffer)][(int)data->posX] == '1') ||
		(newY < data->posY && data->Map[(int)(newY - buffer)][(int)data->posX] == '1'))
		canmoveY = 0;
	if (canmoveX)
	{
		data->posX = newX;
	}
	else if (canmoveX && data->Map[(int)(newY)][(int)(data->posX)] != '1')
	{
		data->posY += (newY - data->posY) * 0.5;
	}
	if (canmoveY)
	{
		data->posY = newY;
	}
	else if (canmoveY && data->Map[(int)(data->posY)][(int)(newX)] != '1')
	{
		data->posX += (newX - data->posX) * 0.5;
	}
	// if (canmoveX || canmoveY)
	// 	redraw(data);
}
