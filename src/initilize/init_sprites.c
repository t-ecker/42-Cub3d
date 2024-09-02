/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:27:44 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/02 19:31:52 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	sprite_position(t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	**map;

	map = data->Map;
	i = -1;
	k = 0;
	while (++i < data->input->map_height)
	{
		j = -1;
		while (++j < data->input->map_width)
		{
			if (map[i][j] == 'M')
			{
				data->sprites[k].y = i + 0.5;
				data->sprites[k].x = j + 0.5;
				k++;
			}
		}
	}
}

void	sprite_attributes(t_data *data)
{
	int	k;

	k = 0;
	while (k < data->sprite_count)
	{
		data->sprites[k].status = 'A';
		data->sprites[k].tex = data->texture->monster;
		k++;
	}
}

int	init_sprites(t_data *data)
{
	data->sprites = malloc(sizeof(t_sprite) * data->sprite_count);
	if (!data->sprites)
		return (1);
	sprite_position(data);
	sprite_attributes(data);
	return (0);
}
