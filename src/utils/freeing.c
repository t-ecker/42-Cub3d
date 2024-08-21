/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:50:32 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/20 15:01:11 by tomecker         ###   ########.fr       */
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

void	free_map(t_input *input)
{
	int	i;

	i = 0;
	while (input->map[i])
	{
		free(input->map[i]);
		i++;
	}
	free(input->map);
}

void	free_input(t_input *input)
{
	free_params(input);
	free_map(input);
	free(input);
}

void	free_cubed(t_cubed *cubed)
{
	free(cubed->title);
	free(cubed);
}

void	free_data(t_data *data)
{
	free(data->wallDistances);
	free(data->hit_side);
	free(data->texture);
	free(data->facing);
	free(data->cdoor);
	free(data->texX);
	free(data->ttu);
	free(data);
}

void	delete_textures(t_data *data)
{
	mlx_delete_texture(data->texture->n);
	mlx_delete_texture(data->texture->s);
	mlx_delete_texture(data->texture->w);
	mlx_delete_texture(data->texture->e);
	mlx_delete_texture(data->texture->F);
	mlx_delete_texture(data->texture->D);
	mlx_delete_texture(data->texture->DO);
	mlx_delete_texture(data->texture->infoF);
	mlx_delete_texture(data->texture->infoD);
	mlx_delete_texture(data->texture->infoDC);
}

void	free_all(t_data *data, t_cubed *cubed, t_input *input)
{
	if (data)
		free_data(data);
	if (cubed)
		free_cubed(cubed);
	if (input)
		free_input(input);
}
