/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:03:04 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/17 17:40:41 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	init_image(t_input *input, t_cubed *cubed, t_data *data)
{
	cubed->bg = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	ceiling_floor(cubed, input);
	cubed->walls = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	setPlane(data);
	castRays(data);
	draw_walls(cubed, data);
	ft_hook(data);
	if (!cubed->bg || (mlx_image_to_window(cubed->mlx, cubed->bg, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_input(input);
		free_cubed(cubed);
		return (0);
	}
	if (!cubed->walls || (mlx_image_to_window(cubed->mlx, cubed->walls, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_input(input);
		free_cubed(cubed);
		return (0);
	}
	mlx_loop(cubed->mlx);
	mlx_terminate(cubed->mlx);
	return (1);
}

t_cubed	*init_cubed(t_input *input, char *filename)
{
	t_cubed	*cubed;

	cubed = malloc(sizeof(t_cubed));
	if (!cubed)
		return (NULL);
	cubed->title = ft_strjoin("cub3d - ", filename);
	cubed->mlx = mlx_init(WIDTH, HEIGHT, cubed->title, 1);
	if (!cubed->mlx)
		return (ft_putendl_fd("Window initialization fail.", 2),
			free_input(input), NULL);
	return (cubed);
}

t_texture *init_texture(t_input *input)
{
	t_texture *texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->n = mlx_load_png(input->wall_n);
	texture->s = mlx_load_png(input->wall_s);
	texture->w = mlx_load_png(input->wall_w);
	texture->e = mlx_load_png(input->wall_e);
	
	if (!texture->n || !texture->s || !texture->w || !texture->e)
		return (NULL);
	return (texture);
}

t_data	*init_data(t_input *input, t_cubed *cubed)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cubed = cubed;
	data->input = input;
	data->texture = init_texture(input);
	data->Map = input->map;
	data->posX = input->pos_x;
	data->posY = input->pos_y;
	data->fov = 90;
	setDir(data, input);
	data->wallDistances = malloc(sizeof(double) * WIDTH);
	if (!data->wallDistances || !data->texture)
	{
		free(data->texture);
		free(data);
		return (NULL);
	}
	data->hit_side = malloc(sizeof(char) * WIDTH);
	if (!data->hit_side)
	{
		free(data->texture);
		free(data->wallDistances);
		free(data);
		return (NULL);
	}
	data->texX = malloc(sizeof(int) * WIDTH);
	if (!data->texX)
	{
		free(data->texture);
		free(data->hit_side);
		free(data->wallDistances);
		free(data);
		return (NULL);
	}
	return (data);
}
