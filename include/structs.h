/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tecker <tecker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:53 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/19 13:56:02 by tecker           ###   ########.fr       */
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
	mlx_image_t	*info;
	mlx_image_t	*victory;
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
	mlx_texture_t *n;
	mlx_texture_t *s;
	mlx_texture_t *w;
	mlx_texture_t *e;
	mlx_texture_t *F;
	mlx_texture_t *D;
	mlx_texture_t *infoF;
	mlx_texture_t *infoD;
	mlx_texture_t *infoDC;
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
	double *cdoor;
	int *texX;
	char *hit_side;
	char *facing;
	t_cubed *cubed;
	t_input *input;
	t_texture *texture;
}	t_data;

#endif
