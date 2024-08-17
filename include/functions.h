/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:57 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/17 23:42:45 by dolifero         ###   ########.fr       */
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
int				check_map(char **map, t_input *input);

//PARSING
void			setDir(t_data *data, t_input *input);
void			setPlane(t_data *data);
t_input			*parse_file(char *filename);
int				init_image(t_input *input, t_cubed *cubed, t_data *data);
int				init_overlay_img(t_cubed *cubed, t_input *input);
int				init_walls_img(t_cubed *cubed, t_input *input);
int				init_bg_img(t_cubed *cubed, t_input *input);
t_cubed			*init_cubed(t_input *input, char *filename);
t_data			*init_data(t_input *input, t_cubed *cubed);
unsigned int	parse_color(char *colors);

//DRAWING
void			my_put_pixel(mlx_image_t *img, int x, int y, int color);
void			ceiling_floor(t_cubed *cubed, t_input *input);
void			draw_walls(t_cubed *cubed, t_data *data);
void			setPlane(t_data *data);
void			redraw(t_data *data);

//CONTROLS
void			ft_window_hook(void *param);
void			movement_hook(t_data *data, mlx_t *mlx);
void			ft_hook(t_data *data);
void			collision(t_data *data, double newX, double newY);

//FREEING
void			free_params(t_input *input);
void			free_input(t_input *input);
void			free_cubed(t_cubed *cubed);
void			free_data(t_data *data);
void			free_all(t_data *data, t_cubed *cubed, t_input *input);

//UTILS
void			remove_newline(char *line);
int				rgb_to_rgba_hex(int r, int g, int b, int a);
void			clear_image(mlx_image_t *image);

//DEBUG
void			print_input(t_input *input);
void			print_map(t_input *input);
void			print_dist(t_data *data);

//wallDist
void			castRays(t_data *data);

#endif
