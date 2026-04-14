/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:09:33 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/14 19:14:24 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

#include <math.h>
#include <stdbool.h>
#include <unistd.h>

static void	left_rotation(t_mlx *mlx)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;
	double		rot_speed;

	p = &mlx->player;
	rot_speed = -p->rot_speed;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
	mlx->screen.need_redraw = true;
}

static void	right_rotation(t_mlx *mlx)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;
	double		rot_speed;

	p = &mlx->player;
	rot_speed = p->rot_speed;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
	mlx->screen.need_redraw = true;
}

static void	move_forward(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (get_map_id(mlx, (int)(p->pos_x + p->dir_x * p->move_speed),
		(int)p->pos_y) == MAP_ROOM)
		p->pos_x += p->dir_x * p->move_speed;
	if (get_map_id(mlx, (int)p->pos_x,
			(int)(p->pos_y + p->dir_y * p->move_speed)) == MAP_ROOM)
		p->pos_y += p->dir_y * p->move_speed;
	mlx->screen.need_redraw = true;
}

static void	move_backward(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (get_map_id(mlx, (int)(p->pos_x - p->dir_x * p->move_speed),
		(int)p->pos_y) == MAP_ROOM)
		p->pos_x -= p->dir_x * p->move_speed;
	if (get_map_id(mlx, (int)p->pos_x,
			(int)(p->pos_y - p->dir_y * p->move_speed)) == MAP_ROOM)
		p->pos_y -= p->dir_y * p->move_speed;
	mlx->screen.need_redraw = true;
}

static void	get_mouse_track(t_mlx *mlx)
{
	int				x;
	int				y;
	double			old_rot_speed;

	mlx_mouse_get_pos(mlx->mlx, &x, &y);
	if (x != mlx->screen.w >> 1)
	{
		old_rot_speed = mlx->player.rot_speed;
		mlx->player.rot_speed = old_rot_speed * 2;
		if (x <  mlx->screen.w >> 1)
			left_rotation(mlx);
		else if (x >  mlx->screen.w >> 1)
			right_rotation(mlx);
		mlx->player.rot_speed = old_rot_speed;
		mlx_mouse_move(mlx->mlx, mlx->win, mlx->screen.w >> 1, mlx->screen.h >> 1);
	}
}

void	movement(t_mlx *mlx)
{
	get_mouse_track(mlx);
	if (mlx->key_tab[KEY_A_INDEX])
		left_rotation(mlx);
	if (mlx->key_tab[KEY_W_INDEX])
		move_forward(mlx);
	if (mlx->key_tab[KEY_S_INDEX])
		move_backward(mlx);
	if (mlx->key_tab[KEY_D_INDEX])
		right_rotation(mlx);
}
