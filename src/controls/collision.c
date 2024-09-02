/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 20:09:09 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	detect(char c)
{
	return (c == '1' || c == 'D' || c == 'F');
}

int	check_x(t_data *data, double new_x, float buffer)
{
	if (detect(data->Map[(int)(data->posY + buffer)][(int)(new_x + buffer)])
	|| detect(data->Map[(int)(data->posY - buffer)][(int)(new_x + buffer)])
	|| detect(data->Map[(int)(data->posY + buffer)][(int)(new_x - buffer)])
	|| detect(data->Map[(int)(data->posY - buffer)][(int)(new_x - buffer)])
	|| detect(data->Map[(int)data->posY][(int)(new_x + buffer)])
	|| detect(data->Map[(int)data->posY][(int)(new_x - buffer)]))
		return (0);
	return (1);
}

int	check_y(t_data *data, double new_y, float buffer)
{
	if (detect(data->Map[(int)(new_y + buffer)][(int)(data->posX + buffer)])
	|| detect(data->Map[(int)(new_y + buffer)][(int)(data->posX - buffer)])
	|| detect(data->Map[(int)(new_y - buffer)][(int)(data->posX + buffer)])
	|| detect(data->Map[(int)(new_y - buffer)][(int)(data->posX - buffer)])
	|| detect(data->Map[(int)(new_y + buffer)][(int)data->posX])
	|| detect(data->Map[(int)(new_y - buffer)][(int)data->posX]))
		return (0);
	return (1);
}

void	collision(t_data *data, double new_x, double new_y)
{
	float	buffer;
	int		canmove_x;
	int		canmove_y;

	buffer = 0.3;
	if (data->Map[(int)new_y][(int)new_x] == 'M')
	{
		data->end = 1;
		clear_image(data->cubed->hand);
		draw_overlay_part(data->cubed->victory, data->texture->death, 0, 0);
		return ;
	}
	canmove_x = check_x(data, new_x, buffer);
	canmove_y = check_y(data, new_y, buffer);
	if (canmove_x && canmove_y)
	{
		data->posX = new_x;
		data->posY = new_y;
	}
	else if (canmove_x)
		data->posX = new_x;
	else if (canmove_y)
		data->posY = new_y;
}
