/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:57 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/15 17:09:28 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "./cubed.h"

//CHECKING
int		ft_isappr(char c);
int		check_args(int argc, char **argv);
int		check_input(t_input *input);
int		check_params(t_input *input);
int		check_map(char **map);

//PARSING
t_input	*parse_file(char *filename);

//DRAWING
void	my_put_pixel(mlx_image_t *img, int x, int y, int color);

//FREEING
void	free_params(t_input *input);
void	free_input(t_input *input);

//UTILS
void	remove_newline(char *line);

//DEBUG
void	print_input(t_input *input);
void	print_map(t_input *input);

#endif
