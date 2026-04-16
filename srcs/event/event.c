/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:47:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/16 16:45:33 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "cub.h"

#include <stdbool.h>
#include <stdint.h>

void	key_hook_up(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	if (key == KEY_A)
		mlx->key_tab[KEY_A_INDEX] = false;
	else if (key == KEY_D)
		mlx->key_tab[KEY_D_INDEX] = false;
	else if (key == KEY_W)
		mlx->key_tab[KEY_W_INDEX] = false;
	else if (key == KEY_S)
		mlx->key_tab[KEY_S_INDEX] = false;
	else if (key == KEY_LEFT)
		mlx->key_tab[KEY_LEFT_INDEX] = false;
	else if (key == KEY_RIGHT)
		mlx->key_tab[KEY_RIGHT_INDEX] = false;
}

static void	manage_mouse(t_mlx *mlx)
{
	const int		center_x = mlx->screen.center_x;
	const int		center_h = mlx->screen.center_h;

	if (mlx->key_tab[KEY_F12_INDEX])
		mlx_mouse_show(mlx->mlx);
	else
	{
		mlx_mouse_hide(mlx->mlx);
		mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_h);
	}
	mlx->key_tab[KEY_F12_INDEX] = !mlx->key_tab[KEY_F12_INDEX];
}

void	key_hook_down(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	if (key == KEY_ESC)
		mlx_loop_end(mlx->mlx);
	if (key == KEY_A)
		mlx->key_tab[KEY_A_INDEX] = true;
	else if (key == KEY_D)
		mlx->key_tab[KEY_D_INDEX] = true;
	else if (key == KEY_LEFT)
		mlx->key_tab[KEY_LEFT_INDEX] = true;
	else if (key == KEY_RIGHT)
		mlx->key_tab[KEY_RIGHT_INDEX] = true;
	else if (key == KEY_W)
		mlx->key_tab[KEY_W_INDEX] = true;
	else if (key == KEY_S)
		mlx->key_tab[KEY_S_INDEX] = true;
	else if (key == KEY_F10)
		mlx->key_tab[KEY_F10_INDEX] = !mlx->key_tab[KEY_F10_INDEX];
	else if (key == KEY_F12)
		manage_mouse(mlx);
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(((t_mlx *)param)->mlx);
}
