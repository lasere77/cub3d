/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:09:33 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/10 17:00:54 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_movement.h"

#include <math.h>

void	left_rotation(t_mlx *mlx)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &mlx->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(p->rot_speed) - p->dir_y * sin(p->rot_speed);
	p->dir_y = old_dir_x * sin(p->rot_speed) + p->dir_y * cos(p->rot_speed);
	p->plane_x = p->plane_x * cos(p->rot_speed) - p->plane_y * sin(p->rot_speed);
	p->plane_y = old_plane_x * sin(p->rot_speed) + p->plane_y * cos(p->rot_speed);
	mlx->screen.need_redraw = true;
}

void	right_rotation(t_mlx *mlx)
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
	mlx->screen.need_redraw = true;
}

void	move_forward(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (worldMap[(int)(p->pos_x + p->dir_x * p->move_speed)][(int)p->pos_y] == 0)
		p->pos_x += p->dir_x * p->move_speed;
    if (worldMap[(int)p->pos_x][(int)(p->pos_y + p->dir_y * p->move_speed)] == 0)
		p->pos_y += p->dir_y * p->move_speed;
	mlx->screen.need_redraw = true;
}

void	move_backward(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	if (worldMap[(int)(p->pos_x - p->dir_x * p->move_speed)][(int)p->pos_y] == 0)
		p->pos_x -= p->dir_x * p->move_speed;
    if (worldMap[(int)p->pos_x][(int)(p->pos_y - p->dir_y * p->move_speed)] == 0)
		p->pos_y -= p->dir_y * p->move_speed;
	mlx->screen.need_redraw = true;
}
