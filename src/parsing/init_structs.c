/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:03:04 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 06:22:48 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

t_input	*init_input(void)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->map_height = 0;
	input->wall_w = NULL;
	input->wall_e = NULL;
	input->wall_n = NULL;
	input->wall_s = NULL;
	input->floor = -1;
	input->ceiling = -1;
	input->map = NULL;
	input->view_dir = '\0';
	input->pos_x = 0;
	input->pos_y = 0;
	return (input);
}

t_cubed	*init_cubed(t_input *input, char *filename)
{
	t_cubed	*cubed;

	cubed = malloc(sizeof(t_cubed));
	if (!cubed)
		return (NULL);
	cubed->title = ft_strjoin("cub3d - ", filename);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
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
	texture->shoot = mlx_load_png("./assets/pistol_shoot.png");
	texture->recoil = mlx_load_png("./assets/pistol_recoil.png");
	texture->hand = mlx_load_png("./assets/pistol_static.png");
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
