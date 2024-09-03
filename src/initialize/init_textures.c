/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:20:51 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/03 17:06:41 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	set_texture(t_texture *texture, t_input *input)
{
	texture->n = mlx_load_png(input->wall_n);
	texture->s = mlx_load_png(input->wall_s);
	texture->w = mlx_load_png(input->wall_w);
	texture->e = mlx_load_png(input->wall_e);
}

int	check_texture1(t_texture *texture)
{
	if (!texture->n)
		return (1);
	if (!texture->s)
		return (1);
	if (!texture->w)
		return (1);
	if (!texture->e)
		return (1);
	return (0);
}

t_texture	*check_texture(t_texture *texture)
{
	if (check_texture1(texture))
		return (NULL);
	return (texture);
}

t_texture	*init_texture(t_input *input)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	set_texture(texture, input);
	return (check_texture(texture));
}
