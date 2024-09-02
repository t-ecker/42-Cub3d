/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:28:00 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 18:23:46 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	setdir(t_data *data, t_input *input)
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

void	setplane(t_data *data)
{
	double	fov;

	fov = data->fov * (M_PI / 180);
	data->planeX = (-(tan(fov / 2))) * data->dirY;
	data->planeY = (tan(fov / 2)) * data->dirX;
}

unsigned int	parse_color(char *colors)
{
	int		hex_color;
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(colors, ',');
	hex_color = 0;
	while (splitted[i])
		i++;
	if (i == 3)
	{
		hex_color = rgb_to_rgba_hex(ft_atoi(splitted[0]),
				ft_atoi(splitted[1]), ft_atoi(splitted[2]), 255);
	}
	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	free(colors);
	return (hex_color);
}
