/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:06:15 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 00:27:32 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	draw_bg(t_data *data, t_input *input)
{
	int		i;
	int		j;
	double	fog_factor;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = -1;
		fog_factor = 1.2 - ((double)(HEIGHT / 2 - i) / (HEIGHT / 2));
		while (++j < WIDTH)
			my_put_pixel(data->cubed->bg, j, i,
				add_fog(input->ceiling, data->weapon, fog_factor, 0));
		i++;
	}
	while (i < HEIGHT)
	{
		j = -1;
		fog_factor = 1.2 - ((double)(i - HEIGHT / 2) / (HEIGHT / 2));
		while (++j < WIDTH)
			my_put_pixel(data->cubed->bg, j, i,
				add_fog(input->ceiling, data->weapon,
					fog_factor, 0));
		i++;
	}
}

void	ft_dark_img(mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_put_pixel(img, j, i, 0x000000FF);
			j++;
		}
		i++;
	}
}
