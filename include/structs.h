/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:21:53 by dolifero          #+#    #+#             */
/*   Updated: 2024/08/16 17:05:28 by tomecker         ###   ########.fr       */
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

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}				t_bresenham;

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
	char		*title;
}				t_cubed;

typedef struct s_point
{
	int x;
	int y;
}	t_point;

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
}	t_data;

#endif
