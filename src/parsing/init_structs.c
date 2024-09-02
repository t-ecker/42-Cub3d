/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:03:04 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/02 17:41:44 by tomecker         ###   ########.fr       */
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
	texture->monster_s = mlx_load_png("./textures/monster2.png");
	texture->pos = mlx_load_png("./assets/player_dot.png");
	if (!texture->n || !texture->s || !texture->w || !texture->e)
		return (NULL);
	return (texture);
}

void	init_sprites(t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	**map;

	map = data->Map;
	i = -1;
	k = 0;
	while (++i < data->input->map_height)
	{
		j = -1;
		while (++j < data->input->map_width)
		{
			if (map[i][j] == 'M')
			{
				data->sprites[k].y = i + 0.5;
				data->sprites[k].x = j + 0.5;
				k++;
			}
		}
	}
	k = 0;
	while (k < data->sprite_count)
	{
		data->sprites[k].status = 'A';
		data->sprites[k].tex = data->texture->monster;
		k++;
	}
}

int	ft_count_enemies(t_data *data, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < data->input->map_height)
	{
		j = 0;
		while (j < data->input->map_width)
		{
			if (data->Map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	ft_printf("\n\ncount: %d\n\n", count);
	return (count);
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
	data->end = 0;
	data->toggle_light = 0;
	data->sprite_count = ft_count_enemies(data, 'M');
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


