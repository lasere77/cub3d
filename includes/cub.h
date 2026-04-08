/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:59:32 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/08 17:19:46 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"

# include <stdint.h>
# include <stddef.h>
# include <sys/time.h>

# define FPS_GOAL 60
# define ALPHA -1 // 0x99

# define MAP_WIDTH 24
# define MAPHEIGHT 24

extern int	worldMap[MAP_WIDTH][MAPHEIGHT];

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_screen
{
	mlx_image	img;
	int			w;
	int			h;
}				t_screen;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	ray_dist;
}			t_ray;

typedef struct s_mlx
{
	mlx_context		mlx;
	mlx_window		win;
	t_player		player;
	t_screen		screen;
	t_ray			ray;
	struct timeval	start;
}					t_mlx;

mlx_color	get_color(int mapX, int mapY, int side);
void		draw(t_mlx *mlx, int x, int h, mlx_color color);
void		check_resolution(t_mlx *mlx);

#endif