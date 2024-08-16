/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:57 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 14:23:09 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "./cubed.h"

//CHECKING
int				ft_isappr(char c);
int				check_args(int argc, char **argv);
int				check_input(t_input *input);
int				check_params(t_input *input);
int				check_map(char **map);

//PARSING
t_input			*parse_file(char *filename);

//DRAWING
void			my_put_pixel(mlx_image_t *img, int x, int y, int color);
void			ceiling_floor(t_cubed *cubed, t_input *input);

//CONTROLS
void			ft_window_hook(void *param);
void			ft_hook(t_cubed *cubed);

//FREEING
void			free_params(t_input *input);
void			free_input(t_input *input);
void			free_cubed(t_cubed *cubed);
void			free_data(t_data *data);
void			free_all(t_data *data, t_cubed *cubed, t_input *input);


//UTILS
void			remove_newline(char *line);
int				rgb_to_rgba_hex(int r, int g, int b, int a);

//DEBUG
void			print_input(t_input *input);
void			print_map(t_input *input);
void			print_dist(t_data *data);

//wallDist
void			castRays(t_data *data);



#endif
