/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:03:04 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/22 16:06:50 by tomecker         ###   ########.fr       */
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
	texture->D = mlx_load_png("./textures/CRATE_2C.PNG");
	texture->DO = mlx_load_png("./textures/CRATE_2M_OPEN.png");
	texture->F = mlx_load_png("./textures/CONSOLE_1B.PNG");
	texture->infoD = mlx_load_png("./assets/1.PNG");
	texture->infoDC = mlx_load_png("./assets/2.PNG");
	texture->infoF = mlx_load_png("./assets/3.PNG");
	texture->shoot = mlx_load_png("./assets/pistol_shoot.png");
	texture->recoil = mlx_load_png("./assets/pistol_recoil.png");
	texture->hand = mlx_load_png("./assets/pistol_static.png");
	texture->light = mlx_load_png("./assets/light.png");
	texture->dark = mlx_load_png("./assets/dark.png");
	texture->victory = mlx_load_png("./assets/victory.png");
	texture->death = mlx_load_png("./assets/death.png");
	texture->flashlight = mlx_load_png("./assets/flashlight_1.png");
	texture->monster = mlx_load_png("./textures/monster.png");
	if (!texture->n || !texture->s || !texture->w || !texture->e)
		return (NULL);
	return (texture);
}

void	init_sprites(t_data *data)
{
	// int i;

	// i = 0;
	// while (i < data->sprite_count)
	data->sprites[0].status = 'A';

	data->sprites[0].x = 2.5;
	data->sprites[0].y = 2.5;
	data->sprites[0].tex = data->texture->monster;

	// data->sprites[1].x = 2.5;
	// data->sprites[1].y = 2.5;
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
	data->weapon = 1;
	data->toggle_light = 0;
	data->sprite_count = 1;
	setDir(data, input);
	data->facing = malloc(sizeof(char) * WIDTH);
	data->sprites = malloc(sizeof(t_sprite) * data->sprite_count);
	data->hit = malloc(sizeof(t_hit *) * WIDTH);
	data->hit_count = malloc(sizeof(int) * WIDTH);
	int x = 0;
	while (x < WIDTH)
	{
		data->hit[x] = malloc(sizeof(t_hit) * 10);
		if (!data->hit[x])
        {
            int j = 0;
            while (j < x)
            {
                free(data->hit[j]);
                j++;
            }
            free(data->hit);
            free(data->hit_count);
            return (NULL);
        }
		data->hit_count[x] = 0;
		x++;
	}
	init_sprites(data);
	return (data);
}


