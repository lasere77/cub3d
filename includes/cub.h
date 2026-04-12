/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:59:32 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/12 14:51:48 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <sys/time.h>

# define FPS_GOAL 600
# define REAL_FPS_GOAL 65
# define ALPHA -1 // 0xFF

typedef enum e_key_index
{
	KEY_ESC_INDEX,
	KEY_F11_INDEX,
	KEY_F12_INDEX,
	KEY_A_INDEX,
	KEY_W_INDEX,
	KEY_S_INDEX,
	KEY_D_INDEX,
	NB_SET_KEY
}	t_key_index;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}			t_player;

typedef struct s_screen
{
	mlx_image		img;
	mlx_color		*buffer;
	double			last_update;
	int				i;
	int				w;
	int				h;
	bool			need_redraw;
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

typedef struct s_txt
{
	mlx_image	img;
	int			w;
	int			h;
	int			is_valid;
}				t_txt;

typedef struct s_map
{
	char		*map;
	t_txt		txt[4];
	mlx_color	floor;
	mlx_color	ceil;
	size_t		w;
	size_t		h;
}				t_map;

typedef struct s_mlx
{
	mlx_context		mlx;
	mlx_window		win;
	t_player		player;
	t_screen		screen;
	t_ray			ray;
	t_map			map;
	struct timeval	start;
	bool			key_tab[NB_SET_KEY];
	double			frame_time;
}					t_mlx;

mlx_color	get_color(t_mlx *mlx, int mapX, int mapY, int side);
void		draw(t_mlx *mlx, int h, mlx_color color);

#endif