/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolifero <dolifero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:53 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 16:29:28 by dolifero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./cubed.h"

typedef struct s_ray
{
	double rayDirX;
	double sideDistX;
	double sideDistY;
	double rayDirY;
	double cameraX;
	int mapY;
	int mapX;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int side;
}	t_ray;

typedef struct s_input
{
	char			**map;
	int				map_height;
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
	mlx_image_t	*hand;
	mlx_image_t	*light;
	char		*title;
}				t_cubed;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int a;
	int final;
}	t_color;

typedef struct s_texture
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
	mlx_texture_t	*shoot;
	mlx_texture_t	*recoil;
	mlx_texture_t	*hand;
	mlx_texture_t	*flashlight;
	mlx_texture_t	*light;
	mlx_texture_t	*dark;
	double step;
	double tex_pos;
	int texY;
	double wall_x;
}	t_texture;

typedef struct s_data
{
	float fov;
	double posX;
	double posY;
	double planeX;
	double planeY;
	double dirX;
	double dirY;
	char **Map;
	double *wallDistances;
	int *texX;
	char *hit_side;
	int	weapon;
	t_cubed *cubed;
	t_input *input;
	t_texture *texture;
}	t_data;

#endif
