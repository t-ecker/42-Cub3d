/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:50:32 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 14:59:39 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	free_params(t_input *input)
{
	if (input->wall_n)
		free(input->wall_n);
	if (input->wall_e)
		free(input->wall_e);
	if (input->wall_w)
		free(input->wall_w);
	if (input->wall_s)
		free(input->wall_s);
}

void	free_input(t_input *input)
{
	int	i;

	free_params(input);
	i = 0;
	while (input->map[i])
	{
		free(input->map[i]);
		i++;
	}
	free(input->map);
	free(input);
}

void	free_hits(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		free(data->hit[x]);
		x++;
	}
	free(data->hit);
	free(data->hit_count);
}

void	free_data(t_data *data)
{
	free(data->sprites);
	delete_img(data);
	free(data->texture);
	free_hits(data);
	free(data);
}

void	free_all(t_data *data, t_cubed *cubed, t_input *input)
{
	if (cubed)
	{
		free(cubed->title);
		free(cubed);
	}
	if (input)
		free_input(input);
	if (data)
		free_data(data);
}
