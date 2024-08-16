/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:21:19 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 02:14:51 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

t_input	*ft_init_input(void)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->map_height = 0;
	input->wall_w = NULL;
	input->wall_e = NULL;
	input->wall_n = NULL;
	input->wall_s = NULL;
	input->floor = 0;
	input->ceiling = 0;
	input->map = NULL;
	return (input);
}

unsigned int	parse_color(char *colors)
{
	int		hex_color;
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(colors, ',');
	hex_color =	rgb_to_rgba_hex(ft_atoi(splitted[0]),
		ft_atoi(splitted[1]), ft_atoi(splitted[2]), 255);
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	free(colors);
	return (hex_color);
}

void	ft_parse_param(char *line, t_input *input)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && input->wall_n == NULL)
		input->wall_n = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0 && input->wall_s == NULL)
		input->wall_s = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0 && input->wall_w == NULL)
		input->wall_w = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0 && input->wall_e == NULL)
		input->wall_e = ft_strdup(line + 3);
	else if (ft_strncmp(line, "C ", 2) == 0 && input->ceiling == 0)
		input->ceiling = parse_color(ft_strdup(line + 3));
	else if (ft_strncmp(line, "F ", 2) == 0 && input->floor == 0)
		input->floor = parse_color(ft_strdup(line + 3));
	else
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Ivalid file content", 2);
		free_params(input);
		exit(1);
	}
}

void	ft_parse_map_line(char *line, t_input *input)
{
	int		i;
	char	**new_map;

	i = 0;
	input->map_height++;
	if (input->map == NULL)
	{
		input->map = malloc(sizeof(char *) * 2);
		input->map[0] = ft_strdup(line);
		input->map[1] = NULL;
	}
	else
	{
		new_map = ft_realloc(input->map, sizeof(char *) * (input->map_height),
				sizeof(char *) * (input->map_height + 1));
		input->map = new_map;
		while (input->map[i] != NULL)
			i++;
		input->map[i] = ft_strdup(line);
		input->map[i + 1] = NULL;
	}
}

t_input	*parse_file(char *filename)
{
	int		fd;
	char	*line;
	t_input	*input;

	input = ft_init_input();
	if (!input)
		return (NULL);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			remove_newline(line);
			if (!check_params(input))
				ft_parse_param(line, input);
			else
				ft_parse_map_line(line, input);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (input);
}
