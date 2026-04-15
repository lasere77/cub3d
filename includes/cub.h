/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:59:32 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/15 14:31:29 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/time.h>

# define FPS_GOAL 120
# define REAL_FPS_GOAL 120
# define ALPHA -1 // 0xFF

# define FONT_SIZE 10

typedef enum e_key_index
{
	KEY_ESC_INDEX,
	KEY_F10_INDEX,
	KEY_F12_INDEX,
	KEY_A_INDEX,
	KEY_W_INDEX,
	KEY_S_INDEX,
	KEY_D_INDEX,
	NB_SET_KEY
}					t_key_index;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct s_screen
{
	mlx_image		img;
	mlx_image		img_mini_map;
	mlx_color		*buffer_mini_map;
	mlx_color		*buffer;
	double			last_update;
	int				wait_second;
	int				i;
	int				w;
	int				h;
	int				center_x;
	int				center_h;
	bool			need_redraw;
}					t_screen;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			ray_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			txt_pos;
	int				txt_x;
	int				txt_y;

}					t_ray;

typedef struct s_txt
{
	mlx_image		img;
	mlx_color		*buffer;
	int				w;
	int				h;
	int				is_valid;
}					t_txt;

typedef struct s_map
{
	char			*map;
	t_txt			txt[4];
	mlx_color		floor;
	mlx_color		ceil;
	size_t			w;
	size_t			h;
	int				map_x;
	int				map_y;
}					t_map;

typedef struct s_mlx
{
	mlx_context		mlx;
	mlx_window		win;
	t_player		player;
	t_screen		screen;
	t_ray			ray;
	t_map			map;
	struct timeval	start;
	double			frame_time;
	bool			key_tab[NB_SET_KEY];
	int				mlx_fps;
}					t_mlx;

void				draw(t_mlx *mlx, int h, int side);

#endif