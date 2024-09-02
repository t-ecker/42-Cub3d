/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:20:51 by tomecker          #+#    #+#             */
/*   Updated: 2024/09/02 19:34:53 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

void	set_texture(t_texture *texture, t_input *input)
{
	texture->n = mlx_load_png(input->wall_n);
	texture->s = mlx_load_png(input->wall_s);
	texture->w = mlx_load_png(input->wall_w);
	texture->e = mlx_load_png(input->wall_e);
	texture->D = mlx_load_png("./textures/CRATE_2C.PNG");
	texture->DO = mlx_load_png("./textures/CRATE_2M_OPEN.png");
	texture->F = mlx_load_png("./textures/CONSOLE_1B.PNG");
	texture->infoD = mlx_load_png("./assets/1.PNG");
	texture->infoDC = mlx_load_png("./assets/2.PNG");
	texture->infoF = mlx_load_png("./assets/3.PNG");
	texture->shoot = mlx_load_png("./assets/pistol_shoot.png");
	texture->recoil = mlx_load_png("./assets/pistol_recoil.png");
	texture->hand = mlx_load_png("./assets/pistol_static.png");
	texture->light = mlx_load_png("./assets/light.png");
	texture->dark = mlx_load_png("./assets/dark.png");
	texture->victory = mlx_load_png("./assets/victory.png");
	texture->death = mlx_load_png("./assets/death.png");
	texture->flashlight = mlx_load_png("./assets/flashlight_1.png");
	texture->monster = mlx_load_png("./textures/monster.png");
	texture->monster_s = mlx_load_png("./textures/monster2.png");
	texture->pos = mlx_load_png("./assets/player_dot.png");
}

int	check_texture2(t_texture *texture)
{
	if (!texture->recoil)
		return (1);
	if (!texture->hand)
		return (1);
	if (!texture->light)
		return (1);
	if (!texture->dark)
		return (1);
	if (!texture->victory)
		return (1);
	if (!texture->death)
		return (1);
	if (!texture->flashlight)
		return (1);
	if (!texture->monster)
		return (1);
	if (!texture->monster_s)
		return (1);
	if (!texture->pos)
		return (1);
	return (0);
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
	if (!texture->D)
		return (1);
	if (!texture->DO)
		return (1);
	if (!texture->F)
		return (1);
	if (!texture->infoD)
		return (1);
	if (!texture->infoDC)
		return (1);
	if (!texture->infoF)
		return (1);
	if (!texture->shoot)
		return (1);
	return (0);
}

t_texture	*check_texture(t_texture *texture)
{
	if (check_texture1(texture) || check_texture2(texture))
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
