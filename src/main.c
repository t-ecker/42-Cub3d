/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:22:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 01:33:23 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	leaks(void)
{
	system("leaks cub3d");
}

int	init_image(t_input *input, t_cubed *cubed)
{
	cubed->bg = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	ceiling_floor(cubed, input);
	ft_hook(cubed);
	if (!cubed->bg || (mlx_image_to_window(cubed->mlx, cubed->bg, 0, 0) < 0))
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
	cubed->title = ft_strjoin("cub3d - ", filename);
	cubed->mlx = mlx_init(WIDTH, HEIGHT, cubed->title, 1);
	if (!cubed->mlx)
		return (ft_putendl_fd("Window initialization fail.", 2),
			free_input(input), NULL);
	return (cubed);
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_cubed	*cubed;

	if (!check_args(argc, argv))
		return (1);
	input = parse_file(argv[1]);
	cubed = init_cubed(input, argv[1]);
	if (!check_input(input))
		return (1);
	print_input(input);
	print_map(input);
	if (!init_image(input, cubed))
		return (1);
	free_input(input);
	free_cubed(cubed);
	return (0);
}
