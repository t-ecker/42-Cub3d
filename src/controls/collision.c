/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 19:28:19 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	detect(char c)
{
	return (c == '1');
}

int	check_x(t_data *data, double new_x, float buffer)
{
	if (detect(data->map[(int)(data->pos_y + buffer)][(int)(new_x + buffer)])
	|| detect(data->map[(int)(data->pos_y - buffer)][(int)(new_x + buffer)])
	|| detect(data->map[(int)(data->pos_y + buffer)][(int)(new_x - buffer)])
	|| detect(data->map[(int)(data->pos_y - buffer)][(int)(new_x - buffer)])
	|| detect(data->map[(int)data->pos_y][(int)(new_x + buffer)])
	|| detect(data->map[(int)data->pos_y][(int)(new_x - buffer)]))
		return (0);
	return (1);
}

int	check_y(t_data *data, double new_y, float buffer)
{
	if (detect(data->map[(int)(new_y + buffer)][(int)(data->pos_x + buffer)])
	|| detect(data->map[(int)(new_y + buffer)][(int)(data->pos_x - buffer)])
	|| detect(data->map[(int)(new_y - buffer)][(int)(data->pos_x + buffer)])
	|| detect(data->map[(int)(new_y - buffer)][(int)(data->pos_x - buffer)])
	|| detect(data->map[(int)(new_y + buffer)][(int)data->pos_x])
	|| detect(data->map[(int)(new_y - buffer)][(int)data->pos_x]))
		return (0);
	return (1);
}

void	collision(t_data *data, double new_x, double new_y)
{
	float	buffer;
	int		canmove_x;
	int		canmove_y;

	buffer = 0.3;
	canmove_x = check_x(data, new_x, buffer);
	canmove_y = check_y(data, new_y, buffer);
	if (canmove_x && canmove_y)
	{
		data->pos_x = new_x;
		data->pos_y = new_y;
	}
	else if (canmove_x)
		data->pos_x = new_x;
	else if (canmove_y)
		data->pos_y = new_y;
}
