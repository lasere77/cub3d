/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:47:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/10 13:33:48 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "cub.h"

#include <math.h>

static void	left_rotation(t_mlx *mlx)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &mlx->player;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
	p->dir_y = old_dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(p->rot_speed) - p->plane_y * sin(p->rot_speed);
	p->plane_y = old_plane_x * sin(p->rot_speed) + p->plane_y * cos(p->rot_speed);
}

static void	right_rotation(t_mlx *mlx)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &mlx->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(-p->rot_speed) - p->dir_y * sin(-p->rot_speed);
	p->dir_y = old_dir_x * sin(-p->rot_speed) + p->dir_y * cos(-p->rot_speed);
    p->plane_x = p->plane_x * cos(-p->rot_speed) - p->plane_y * sin(-p->rot_speed);
    p->plane_y = old_plane_x * sin(-p->rot_speed) + p->plane_y * cos(-p->rot_speed);
}

void	key_hook(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	if (key == KEY_ESC)
		mlx_loop_end(mlx->mlx);
	else if (key == KEY_A)
		left_rotation(mlx);
	else if (key == KEY_D)
		right_rotation(mlx);
	else if (key == KEY_F11)
		mlx_set_window_fullscreen(mlx->mlx, mlx->win, 1);
	else if (key == KEY_F12)
		mlx_set_window_fullscreen(mlx->mlx, mlx->win, 0);
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(((t_mlx *)param)->mlx);
}
