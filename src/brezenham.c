/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:24:08 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/15 17:10:08 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	my_put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
		mlx_put_pixel(img, x, y, color);
}

void	init_line_params(t_point src, t_point dest, t_bresenham *params)
{
	params->dx = abs(dest.x - src.x);
	params->dy = abs(dest.y - src.y);
	if (src.x < dest.x)
		params->sx = 1;
	else
		params->sx = -1;
	if (src.y < dest.y)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx - params->dy;
}

void	bresenham_line(mlx_image_t *img, t_point src, t_point dest,
		t_bresenham params)
{
	int	e2;

	while (1)
	{
		my_put_pixel(img, src.x, src.y, 0xFFFFFFFF);
		if (src.x == dest.x && src.y == dest.y)
			break ;
		e2 = params.err * 2;
		if (e2 > -params.dy)
		{
			params.err -= params.dy;
			src.x += params.sx;
		}
		if (e2 < params.dx)
		{
			params.err += params.dx;
			src.y += params.sy;
		}
	}
}
