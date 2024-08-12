/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:46:29 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/12 02:12:36 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	print_input(t_input *input)
{
	ft_printf("\n");
	ft_printf("%s\n", input->wall_n);
	ft_printf("%s\n", input->wall_s);
	ft_printf("%s\n", input->wall_w);
	ft_printf("%s\n", input->wall_e);
	ft_printf("\n");
	ft_printf("%s\n", input->ceiling);
	ft_printf("%s\n", input->floor);
	ft_printf("\n");
}
