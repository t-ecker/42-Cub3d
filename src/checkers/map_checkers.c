/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 03:42:11 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/27 20:33:11 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	check_map_characters(char **map, t_input *input)
{
	int	i;
	int	j;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (!ft_isappr(map[j][i]))
				return (0);
			if ((map[j][i] == 'N' || map[j][i] == 'W' || map[j][i] == 'S'
				|| map[j][i] == 'E'))
			{
				if (!input->view_dir)
				{
					input->view_dir = map[j][i];
					input->pos_x = (double)i + 0.5;
					input->pos_y = (double)j + 0.5;
				}
				else
					return (0);
			}
		}
	}
	return (1);
}

int	check_map_horizontal(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][0] != '1' && map[j][0] != ' ')
				return (0);
			if (map[j][i + 1] == '\0' && map[j][i] != '1' && map[j][i] != ' ')
				return (0);
			if (i > 0 && map[j][i] == ' '
				&& (map[j][i - 1] != '1' && map[j][i - 1] != ' '))
				return (0);
			if (i > 0 && (map[j][i] != '1' && map[j][i] != ' ')
				&& map[j][i - 1] == ' ')
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	check_map_vertical(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[0][i])
	{
		j = 0;
		if (map[0][i] != '1' && map[0][i] != ' ')
			return (0);
		while (map[j])
		{
			if (map[j + 1] == NULL && map[j][i] != '1' && map[j][i] != ' ')
				return (0);
			if (j > 0 && map[j][i] == ' '
				&& (map[j - 1][i] != '1' && map[j - 1][i] != ' '))
				return (0);
			if (j > 0 && (map[j][i] != '1' && map[j][i] != ' ')
				&& map[j - 1][i] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_sides(char **map, int x, int y, t_input *input)
{
	if (x > 0 && x < input->map_width - 1)
		if (map[y][x - 1] == '1' && map[y][x + 1] == '1')
			return (1);
	if (y > 0 && y < input->map_height - 1)
		if (map[y - 1][x] == '1' && map[y + 1][x] == '1')
			return (1);
	return (0);
}

int	check_map_doors(char **map, t_input *input)
{
	int x;
	int y;

	y = 0;
	while (y < input->map_height)
	{
		x = 0;
		while (x < input->map_width)
		{
			if (map[y][x] == 'D')
				if (!check_sides(map, x, y, input))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map(char **map, t_input *input)
{
	if (!check_map_characters(map, input))
		return (0);
	if (!input->view_dir)
		return (0);
	pad_strings(map);
	if (!check_map_horizontal(map))
		return (0);
	if (!check_map_vertical(map))
		return (0);
	if (!check_map_doors(map, input))
		return (0);
	return (1);
}
