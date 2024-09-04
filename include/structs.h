/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:53 by dolifero          #+#    #+#             */
/*   Updated: 2024/09/04 11:47:04 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./cubed.h"

typedef struct s_ray
{
	double	raydir_x;
	double	sidedist_x;
	double	sidedist_y;
	double	raydir_y;
	double	camera_x;
	int		map_y;
	int		map_x;
	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

typedef struct s_input
{
	char			**map;
	int				map_height;
	int				map_width;
	char			*wall_n;
	char			*wall_e;
	char			*wall_w;
	char			*wall_s;
	int				floor;
	int				ceiling;
	double			pos_x;
	double			pos_y;
	char			view_dir;
}				t_input;

typedef struct s_cubed
{
	mlx_t		*mlx;
	mlx_image_t	*bg;
	mlx_image_t	*walls;
	mlx_image_t	*overlay;
	mlx_image_t	*info;
	mlx_image_t	*victory;
	mlx_image_t	*hand;
	mlx_image_t	*minimap;
	mlx_image_t	*pos;
	mlx_image_t	*light;
	char		*title;
}				t_cubed;

typedef struct s_sprite
{
	double			x;
	double			y;
	char			status;
	mlx_texture_t	*tex;
}	t_sprite;

typedef struct s_hit
{
	double			distance;
	char			type;
	int				tex_x;
	mlx_texture_t	*tex;
	int				sprite_t;
}			t_hit;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
	int	final;
}	t_color;

typedef struct s_texture
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
	mlx_texture_t	*f;
	mlx_texture_t	*d;
	mlx_texture_t	*k;
	mlx_texture_t	*infof;
	mlx_texture_t	*infod;
	mlx_texture_t	*infok;
	mlx_texture_t	*shoot;
	mlx_texture_t	*recoil;
	mlx_texture_t	*hand;
	mlx_texture_t	*flashlight;
	mlx_texture_t	*light;
	mlx_texture_t	*dark;
	mlx_texture_t	*victory;
	mlx_texture_t	*death;
	mlx_texture_t	*monster;
	mlx_texture_t	*monster_s;
	mlx_texture_t	*crosshair;
	mlx_texture_t	*pos;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				start_y;
	int				end_y;
	int				tex_x;
	double			transform_x;
	double			transform_y;
	int				height;
	double			invdet;
	double			wall_x;
}	t_texture;

typedef struct s_data
{
	float		fov;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
	char		**map;
	int			*hit_count;
	int			sprite_count;
	char		facing;
	int			weapon;
	double		speed;
	int			minimap;
	int			toggle_light;
	int			end;
	t_cubed		*cubed;
	t_input		*input;
	t_texture	*texture;
	t_hit		**hit;
	t_sprite	*sprites;
}	t_data;

#endif
