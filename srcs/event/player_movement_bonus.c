/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 08:42:24 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/15 15:09:01 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"
#include "player_movement.h"
#include "player_movement_bonus.h"

void	strafe_left(t_mlx *mlx)
{
	t_player	*p;
	double		side_x;
	double		side_y;
	int			x;
	int			y;

	p = &mlx->player;
	side_x = p->dir_y;
	side_y = -p->dir_x;
	x = p->pos_x + side_x * (p->move_speed + 0.2);
	y = p->pos_y;
	if (get_map_id(mlx, x, y) == MAP_ROOM)
		p->pos_x += side_x * p->move_speed;
	x = p->pos_x;
	y = p->pos_y + side_y * (p->move_speed + 0.2);
	if (get_map_id(mlx, x, y) == MAP_ROOM)
		p->pos_y += side_y * p->move_speed;
	mlx->screen.need_redraw = true;
}

void	strafe_right(t_mlx *mlx)
{
	t_player	*p;
	double		side_x;
	double		side_y;
	int			x;
	int			y;

	p = &mlx->player;
	side_x = -p->dir_y;
	side_y = p->dir_x;
	x = p->pos_x + side_x * (p->move_speed + 0.2);
	y = p->pos_y;
	if (get_map_id(mlx, x, y) == MAP_ROOM)
		p->pos_x += side_x * p->move_speed;
	x = p->pos_x;
	y = p->pos_y + side_y * (p->move_speed + 0.2);
	if (get_map_id(mlx, x, y) == MAP_ROOM)
		p->pos_y += side_y * p->move_speed;
	mlx->screen.need_redraw = true;
}

void	get_mouse_track(t_mlx *mlx)
{
	const double	old_rot_speed = mlx->player.rot_speed;
	const int		center_x = mlx->screen.center_x;
	const int		center_h = mlx->screen.center_h;
	int				x;
	int				y;

	mlx_mouse_get_pos(mlx->mlx, &x, &y);
	if (x == center_x)
		return ;
	mlx->player.rot_speed = (double)(x - center_x) / MOUSE_SPEED;
	right_rotation(mlx);
	mlx->player.rot_speed = old_rot_speed;
	mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_h);
}
