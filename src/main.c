/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:22:58 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/18 00:16:34 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	leaks(void)
{
	system("leaks cub3d");
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
		return (free_all(data, cubed, input), write(1, "tit\n", 4), 1);
	print_input(input);
	print_map(input);
	if (!init_image(input, cubed, data))
		return (1);
	free_all(data, cubed, input);
	return (0);
}
