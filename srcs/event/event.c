/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:47:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/10 16:11:37 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "cub.h"
#include "player_movement.h"

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
	else if (key == KEY_W)
		move_forward(mlx);
	else if (key == KEY_S)
		move_backward(mlx);
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
