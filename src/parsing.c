/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:21:19 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/12 02:11:46 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

t_input	*ft_init_input(void)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->wall_w = NULL;
	input->wall_e = NULL;
	input->wall_n = NULL;
	input->wall_s = NULL;
	input->floor = NULL;
	input->ceiling = NULL;
	return (input);
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
	else if (ft_strncmp(line, "C ", 2) == 0 && input->ceiling == NULL)
		input->ceiling = ft_strdup(line + 2);
	else if (ft_strncmp(line, "F ", 2) == 0 && input->floor == NULL)
		input->floor = ft_strdup(line + 2);
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
			ft_parse_param(line, input);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (input);
}
