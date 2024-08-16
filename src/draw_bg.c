/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:06:15 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 01:51:10 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	ceiling_floor(t_cubed *cubed, t_input *input)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
			mlx_put_pixel((*cubed).bg, j, i, input->ceiling);
	}
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			mlx_put_pixel((*cubed).bg, j, i, input->floor);
	}
}
