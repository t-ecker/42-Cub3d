/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:57 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/03 13:52:13 by tomecker         ###   ########.fr       */
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
int				check_map_doors(char **map, t_input *input);
int				check_sides(char **map, int x, int y, t_input *input);
int				check_map_vertical(char **map);
int				check_map_horizontal(char **map);
int				check_map_characters(char **map, t_input *input, int j);

//INITILISATION
void			setdir(t_data *data, t_input *input);
void			setplane(t_data *data);
t_input			*parse_file(char *filename);
t_input			*init_input(void);
t_cubed			*init_cubed(t_input *input, char *filename);
t_data			*init_data(t_input *input, t_cubed *cubed);
int				init_overlay_img(t_cubed *cubed, t_input *input, t_data *data);
int				init_walls_img(t_cubed *cubed, t_input *input, t_data *data);
int				init_bg_img(t_cubed *cubed, t_input *input, t_data *data);
int				init_info_img(t_cubed *cubed, t_input *input, t_data *data);
int				init_victory_img(t_cubed *cubed, t_input *input, t_data *data);
t_texture		*init_texture(t_input *input);
int				init_sprites(t_data *data);
unsigned int	parse_color(char *colors);

//DRAWING
int				add_fog(int color, int fog, double fog_factor, double distance);
void			my_put_pixel(mlx_image_t *img, int x, int y, int color);
void			draw(t_data *data);
void			draw_overlay(t_data *data);
void			draw_hand(t_data *data);
void			ft_dark_img(mlx_image_t *img);
void			setplane(t_data *data);
int				get_texture_color(mlx_texture_t *texture, int x, int y);
void			draw_info(t_data *data, char flag);
void			draw_bg(t_data *data, t_input *input);
void			draw_overlay_part(mlx_image_t *img,
					mlx_texture_t *texture, int dst_x, int dst_y);
int				ft_minimap(t_data *data);
void			redraw(void *param);
void			draw_sprites(t_data *data, int x, int hit_c);
int				get_texture_color(mlx_texture_t *texture, int x, int y);
void			my_put_pixel(mlx_image_t *img, int x, int y, int color);
int				is_pixel_transp(mlx_image_t *image, int x, int y);
int				add_fog(int color, int fog, double fog_factor, double distance);

//CONTROLS
void			ft_window_hook(struct mlx_key_data key, void *param);
void			ft_movement_hook(void *param);
void			ft_camera_hook(void *param);
void			ft_cursor_camera_hook(void *param);
void			ft_shoot_hook(struct mlx_key_data key, void *param);
void			ft_mouse_shoot_hook(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);
void			ft_light_hook(struct mlx_key_data key, void *param);
void			ft_hook(t_data *data);
void			collision(t_data *data, double newX, double newY);
int				get_sprite(t_data *data);
void			move_forward(t_data *data, double speed);
void			move_right(t_data *data, double speed);
void			change_door(t_data *data);
int				check_door_collision(t_data *data);
void			change_weapon(t_data *data, int weapon);

//FREEING
void			free_params(t_input *input);
void			free_input(t_input *input);
void			free_hits(t_data *data);
void			free_data(t_data *data);
void			free_all(t_data *data, t_cubed *cubed, t_input *input);

//UTILS
void			remove_newline(char *line);
int				rgb_to_rgba_hex(int r, int g, int b, int a);
void			clear_image(mlx_image_t *image);
char			*ft_str_char_rm(char *str, char c);
void			pad_strings(char **arr, int i);
int				ft_count_map(t_data *data, char c);

//DEBUG
void			print_input(t_input *input);
void			print_map(t_input *input);

//raycasting
void			castrays(t_data *data);
int				dda(t_data *data, t_ray *ray, int x, int *hit_c);
void			initilisation(t_data *data, t_ray *ray, int x, int *hit_c);
void			get_tex_x(t_data *data, t_ray ray, int x, int hc);
int				check_sprites(t_data *data, int x, int hit_c, t_ray ray);
#endif
