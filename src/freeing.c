/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:50:32 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/12 01:53:49 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	free_params(t_input *input)
{
	if (input->wall_n)
		free(input->wall_n);
	if (input->wall_e)
		free(input->wall_e);
	if (input->wall_w)
		free(input->wall_w);
	if (input->wall_s)
		free(input->wall_s);
	if (input->ceiling)
		free(input->ceiling);
	if (input->floor)
		free(input->floor);
}

void	free_input(t_input *input)
{
	free_params(input);
	free(input);
}
