/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 02:09:50 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 02:25:50 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	clamp(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

void	remove_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	rgb_to_rgba_hex(int r, int g, int b, int a)
{
	int	rgba;

	r = clamp(r);
	g = clamp(g);
	b = clamp(b);
	a = clamp(a);

	rgba = (r << 24) | (g << 16) | (b << 8) | a;
	return (rgba);
}
