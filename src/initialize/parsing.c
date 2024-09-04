/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:21:19 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/04 03:36:11 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	ft_parse_param(char *line, t_input *input)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && input->wall_n == NULL)
		input->wall_n = ft_strtrim(line + 2, " \t");
	else if (ft_strncmp(line, "SO ", 3) == 0 && input->wall_s == NULL)
		input->wall_s = ft_strtrim(line + 2, " \t");
	else if (ft_strncmp(line, "WE ", 3) == 0 && input->wall_w == NULL)
		input->wall_w = ft_strtrim(line + 2, " \t");
	else if (ft_strncmp(line, "EA ", 3) == 0 && input->wall_e == NULL)
		input->wall_e = ft_strtrim(line + 2, " \t");
	else if (ft_strncmp(line, "C ", 2) == 0 && input->ceiling == -1)
		input->ceiling = parse_color(ft_str_char_rm(line + 1, ' '));
	else if (ft_strncmp(line, "F ", 2) == 0 && input->floor == -1)
		input->floor = parse_color(ft_str_char_rm(line + 1, ' '));
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
		input->map_width = ft_strlen(line);
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
		if (ft_strlen(line) > input->map_width)
			input->map_width = ft_strlen(line);
		input->map[i + 1] = NULL;
	}
}

t_input	*parse_file(char *filename)
{
	int		fd;
	char	*line;
	t_input	*input;

	input = init_input();
	if (!input)
		return (ft_putendl_fd("Input allocation failed", 2), NULL);
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
	if (!input->map)
		return (ft_putendl_fd("Map is missing", 2), free_params(input), NULL);
	return (input);
}
