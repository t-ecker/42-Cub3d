/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:22:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 20:08:44 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	leaks(void)
{
	system("leaks cub3d");
}

int	init_image(t_input *input, t_cubed *cubed, t_data *data)
{
	cubed->bg = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	ceiling_floor(cubed, input);
	ft_hook(data);
	if (!cubed->bg || (mlx_image_to_window(cubed->mlx, cubed->bg, 0, 0) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_input(input);
		free_cubed(cubed);
		return (0);
	}
	cubed->walls = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	draw_walls(cubed, data);
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

void	setDir(t_data *data, t_input *input)
{
	if (input->view_dir == 'N' || input->view_dir == 'S')
	{
		if (input->view_dir == 'N')
		{
			data->dirX = 0.0;
			data->dirY = -1.0;
		}
		else
		{
			data->dirX = 0.0;
			data->dirY = 1.0;
		}
	}
	else
	{
		if (input->view_dir == 'E')
		{
			data->dirX = 1.0;
			data->dirY = 0.0;
		}
		else
		{
			data->dirX = -1.0;
			data->dirY = 0.0;
		}
	}
}

void	setPlane(t_data *data)
{
	double fov;

	fov = data->fov * (M_PI / 180);
	data->planeX = (-(tan(fov / 2))) * data->dirY;
	data->planeY = (tan(fov / 2)) * data->dirX;
}

t_data	*init_data(t_input *input, t_cubed *cubed)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cubed = cubed;

	data->Map = input->map;

	data->posX = input->pos_x;
	data->posY = input->pos_y;

	data->fov = 90;
	setDir(data, input);
	setPlane(data);

	data->wallDistances = malloc(sizeof(double) * WIDTH);
	if (!data->wallDistances)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_cubed	*cubed;
	t_data	*data;
	if (!check_args(argc, argv))
		return (1);

	input = parse_file(argv[1]);
	if (!check_input(input))
		return (1);
	cubed = init_cubed(input, argv[1]);
	data = init_data(input, cubed);
	if (!data || !cubed)
		return (free_all(data, cubed, input), write(1, "tot\n", 4), 1);
	printf("%ihi\n", input->map_height);
	castRays(data);

	write(1, "ll\n", 3);
	print_input(input);
	print_map(input);
	print_dist(data);
	if (!init_image(input, cubed, data))
		return (1);
	printf("dir: %c\n", input->view_dir);
	free_all(data, cubed, input);

	return (0);
}
