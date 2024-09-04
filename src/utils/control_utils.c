/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:16 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 19:25:21 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	move_forward(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->dir_x / speed;
	new_y = data->pos_y + data->dir_y / speed;
	collision(data, new_x, new_y);
}

void	move_right(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->plane_x / speed;
	new_y = data->pos_y + data->plane_y / speed;
	collision(data, new_x, new_y);
}
