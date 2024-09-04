/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:03:04 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 14:21:42 by tomecker         ###   ########.fr       */
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
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cubed->mlx = mlx_init(WIDTH, HEIGHT, cubed->title, 1);
	mlx_set_cursor_mode(cubed->mlx, MLX_MOUSE_DISABLED);
	if (!cubed->mlx)
		return (ft_putendl_fd("Window initialization fail.", 2),
			free_input(input), NULL);
	return (cubed);
}

int	init_hit(t_data *data)
{
	int	x;
	int	j;

	data->hit = malloc(sizeof(t_hit *) * WIDTH);
	if (!data->hit)
		return (1);
	data->hit_count = malloc(sizeof(int) * WIDTH);
	if (!data->hit_count)
		return (free(data->hit), 1);
	x = -1;
	while (++x < WIDTH)
	{
		data->hit[x] = malloc(sizeof(t_hit) * 10);
		if (!data->hit[x])
		{
			j = -1;
			while (++j < x)
				free(data->hit[j]);
			free(data->hit);
			free(data->hit_count);
			return (1);
		}
		data->hit_count[x] = 0;
	}
	return (0);
}

void	init_simple_data(t_data *data, t_input *input, t_cubed *cubed)
{
	data->cubed = cubed;
	data->input = input;
	data->map = input->map;
	data->pos_x = input->pos_x;
	data->pos_y = input->pos_y;
	data->fov = 90;
	data->speed = 0.05;
	data->weapon = 1;
	data->minimap = 0;
	data->end = 0;
	data->facing = '0';
	data->toggle_light = 0;
	data->sprite_count = ft_count_map(data, 'M');
}

t_data	*init_data(t_input *input, t_cubed *cubed)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	init_simple_data(data, input, cubed);
	data->texture = init_texture(input);
	if (!data->texture)
		return (free(data), NULL);
	if (init_hit(data))
		return (free(data->texture), free(data), NULL);
	if (init_sprites(data))
		return (free_hits(data), free(data->texture), free(data), NULL);
	setdir(data, input);
	setplane(data);
	return (data);
}
