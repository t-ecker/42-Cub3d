/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 17:03:55 by tomecker         ###   ########.fr       */
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
	buffer = 0.3;
  if ((ft_strchr("1D", data->Map[(int)data->posY][(int)(newX + buffer)]) && newX > data->posX) ||
        (ft_strchr("1D", data->Map[(int)data->posY][(int)(newX - buffer)]) && newX < data->posX))
     canmoveX = 0;

  if ((ft_strchr("1D", data->Map[(int)(newY + buffer)][(int)data->posX]) && newY > data->posY) ||
        (ft_strchr("1D", data->Map[(int)(newY - buffer)][(int)data->posX]) && newY < data->posY))
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

}
