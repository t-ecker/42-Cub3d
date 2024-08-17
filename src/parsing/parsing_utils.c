/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:28:00 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/17 01:51:25 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	setDir(t_data *data, t_input *input)
{
	if (input->view_dir == 'N' || input->view_dir == 'S')
	{
		if (input->view_dir == 'N')
			data->dirY = -1.0;
		else
			data->dirY = 1.0;
		data->dirX = 0.0;
	}
	else
	{
		if (input->view_dir == 'E')
			data->dirX = 1.0;
		else
			data->dirX = -1.0;
		data->dirY = 0.0;
	}
}

void	setPlane(t_data *data)
{
	double fov;

	fov = data->fov * (M_PI / 180);
	data->planeX = (-(tan(fov / 2))) * data->dirY;
	data->planeY = (tan(fov / 2)) * data->dirX;
}
