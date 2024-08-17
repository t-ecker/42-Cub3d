/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 03:42:11 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/17 01:26:04 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	check_map_characters(char **map, t_input *input)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
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
			i++;
		}
		j++;
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
				return (ft_printf("1\n"), 0);
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

int	check_map_top_bottom(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			return (0);
		i++;
	}
	while (map[j])
		j++;
	j--;
	i = 0;
	while (map[j][i])
	{
		if (map[j][i] != '1' && map[j][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_map(char **map, t_input *input)
{
	if (!check_map_characters(map, input))
		return (0);
	// if (!input->view_dir)
	// 	return (0);
	if (!check_map_horizontal(map))
		return (0);
	if (!check_map_top_bottom(map))
		return (0);
	return (1);
}
