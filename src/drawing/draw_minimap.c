/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:09:54 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/22 13:17:38 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	ft_draw_minimap_cube(int dst_x, int dst_y, unsigned int color,
	mlx_image_t *img)
{
	int	i;
	int	j;
	int	size;

	size = 10;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_put_pixel(img, dst_x + j, dst_y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_minimap(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	cube_size;

	i = 0;
	y = 0;
	cube_size = 10;
	while (i < data->input->map_height)
	{
		j = 0;
		x = 0;
		while (j < data->input->map_width)
		{
			if (data->Map[i][j] == '1')
				ft_draw_minimap_cube(x, y, 0x444444FF, data->cubed->minimap);
			else if (data->Map[i][j] == '0' || data->Map[i][j] == 'W' || data->Map[i][j] == 'S' || data->Map[i][j] == 'N' || data->Map[i][j] == 'E')
				ft_draw_minimap_cube(x, y, 0x00000000, data->cubed->minimap);
			else if (data->Map[i][j] == 'F')
				ft_draw_minimap_cube(x, y, 0x00CF12FF, data->cubed->minimap);
			else if (data->Map[i][j] == 'D' || data->Map[i][j] == 'K')
				ft_draw_minimap_cube(x, y, 0xEFEB00FF, data->cubed->minimap);
			x += cube_size;
			j++;
		}
		y += cube_size;
		i++;
	}
}

void	minimap_player_pos(void *param)
{
	t_data	*data;
	int		pos_x;
	int		pos_y;

	data = (t_data *)param;
	pos_x = data->posX * 10 - 2;
	pos_y = data->posY * 10 - 2;
	mlx_delete_image(data->cubed->mlx, data->cubed->pos);
	data->cubed->pos = mlx_texture_to_image(data->cubed->mlx, data->texture->pos);
	mlx_image_to_window(data->cubed->mlx, data->cubed->pos, 25 + pos_x,
		HEIGHT - (data->input->map_height * 10) - 25 + pos_y);
}

int	ft_minimap(t_data *data)
{
	int	width;
	int	height;

	width = data->input->map_width * 10;
	height = data->input->map_height * 10;
	data->cubed->minimap = mlx_new_image(data->cubed->mlx, width, height);
	if (!data->cubed->minimap
		|| (mlx_image_to_window(data->cubed->mlx,
				data->cubed->minimap, 25, HEIGHT - height - 25) < 0))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		free_all(data, data->cubed, data->input);
		return (0);
	}
	ft_draw_minimap(data);
	data->cubed->pos = mlx_new_image(data->cubed->mlx, 5, 5);
	mlx_loop_hook(data->cubed->mlx, minimap_player_pos, data);
	return (1);
}
