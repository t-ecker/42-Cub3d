/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:57 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:12 by dolifero         ###   ########.fr       */
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
t_input			*init_input(void);
t_cubed			*init_cubed(t_input *input, char *filename);
t_data			*init_data(t_input *input, t_cubed *cubed);
int				init_image(t_input *input, t_cubed *cubed, t_data *data);
int				init_overlay_img(t_cubed *cubed, t_input *input, t_data *data);
int				init_walls_img(t_cubed *cubed, t_input *input, t_data *data);
int				init_bg_img(t_cubed *cubed, t_input *input, t_data *data);
unsigned int	parse_color(char *colors);

//DRAWING
void			my_put_pixel(mlx_image_t *img, int x, int y, int color);
void			ceiling_floor(t_cubed *cubed, t_input *input);
void			draw_walls(t_cubed *cubed, t_data *data);
void			draw_overlay(t_data *data);
void			draw_hand(t_data *data);
void			ft_dark_img(mlx_image_t *img);
void			setPlane(t_data *data);
int				get_texture_color(mlx_texture_t *texture, int x, int y);
void			redraw(void *param);

//CONTROLS
void			ft_window_hook(struct mlx_key_data key, void *param);
void			ft_movement_hook(void *param);
void			ft_camera_hook(void *param);
void			ft_shoot_hook(struct mlx_key_data key, void *param);
void			ft_light_hook(struct mlx_key_data key, void *param);
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
char			*ft_str_char_rm(char *str, char c);
void			pad_strings(char **arr);

//DEBUG
void			print_input(t_input *input);
void			print_map(t_input *input);
void			print_dist(t_data *data);

//wallDist
void			castRays(t_data *data);

#endif
