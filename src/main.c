/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:22:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 10:13:25 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	leaks(void)
{
	system("leaks cub3d");
}

void	ft_hook(t_data *data)
{
	mlx_loop_hook(data->cubed->mlx, ft_camera_hook, data);
	mlx_loop_hook(data->cubed->mlx, ft_cursor_camera_hook, data);
	mlx_mouse_hook(data->cubed->mlx, ft_mouse_shoot_hook, data);
	mlx_key_hook(data->cubed->mlx, ft_window_hook, data);
	mlx_loop_hook(data->cubed->mlx, ft_movement_hook, data);
}

int	init_image(t_input *input, t_cubed *cubed, t_data *data)
{
	setplane(data);
	castrays(data);
	ft_hook(data);
	if (!init_bg_img(cubed, input, data))
		return (0);
	if (!init_walls_img(cubed, input, data))
		return (0);
	if (!init_overlay_img(cubed, input, data))
		return (0);
	if (!ft_minimap(data))
		return (0);
	if (!init_info_img(cubed, input, data))
		return (0);
	if (!init_victory_img(cubed, input, data))
		return (0);
	mlx_loop_hook(cubed->mlx, redraw, data);
	mlx_loop(cubed->mlx);
	mlx_terminate(cubed->mlx);
	return (1);
}

t_data	*init_structs(char **argv)
{
	t_input	*input;
	t_cubed	*cubed;
	t_data	*data;

	input = parse_file(argv[1]);
	if (!check_input(input))
		return (NULL);
	cubed = init_cubed(input, argv[1]);
	if (!cubed)
		return (free_input(input), NULL);
	data = init_data(input, cubed);
	if (!data)
		return (mlx_terminate(cubed->mlx), free_all(data, cubed, input), NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_args(argc, argv))
		return (1);
	data = init_structs(argv);
	if (!data)
		return (1);
	if (!init_image(data->input, data->cubed, data))
		return (1);
	// print_input(input);
	// print_map(input);
	free_all(data, data->cubed, data->input);
	return (0);
}
