/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:22:38 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 16:56:07 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

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
