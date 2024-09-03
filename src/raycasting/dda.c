/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:23:20 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 19:29:47 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	move(t_ray *ray)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->deltadist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->sidedist_y += ray->deltadist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

int	dda(t_data *data, t_ray *ray, int x, int *hit_c)
{
	int	hit;

	(void)hit_c;
	(void)x;
	hit = 0;
	move(ray);
	if (ft_strchr("1", data->map[ray->map_y][ray->map_x]))
		hit = 1;
	return (hit);
}
