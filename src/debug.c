/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:46:29 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 02:10:35 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	print_input(t_input *input)
{
	ft_printf("\n");
	ft_printf("Wall N: %s\n", input->wall_n);
	ft_printf("Wall S: %s\n", input->wall_s);
	ft_printf("Wall W: %s\n", input->wall_w);
	ft_printf("Wall E: %s\n", input->wall_e);
	ft_printf("\n");
	ft_printf("Ceiling color: %X\n", input->ceiling);
	ft_printf("Floor color: %X\n", input->floor);
	ft_printf("\n");
}

void	print_map(t_input *input)
{
	int	i;

	i = 0;
	while (input->map[i])
	{
		ft_printf("%s\n", input->map[i]);
		i++;
	}
}
