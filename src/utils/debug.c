/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:46:29 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 10:21:06 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	print_input(t_input *input)
{
	printf("\n");
	printf("Wall N: %s\n", input->wall_n);
	printf("Wall S: %s\n", input->wall_s);
	printf("Wall W: %s\n", input->wall_w);
	printf("Wall E: %s\n", input->wall_e);
	printf("\n");
	printf("Ceiling color: %X\n", input->ceiling);
	printf("Floor color: %X\n", input->floor);
	printf("\n");
	printf("Player posY: %f\n", input->pos_y);
	printf("Player posX: %f\n", input->pos_x);
	printf("View direction: %c\n", input->view_dir);
	printf("\n");
	printf("Map height: %d\n", input->map_height);
	printf("Map width: %d\n", input->map_width);
	printf("\n");
}

void	print_map(t_input *input)
{
	int	i;

	i = 0;
	while (input->map[i])
	{
		printf("%s\n", input->map[i]);
		i++;
	}
	printf("\n");
}
