/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:47:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/13 14:34:40 by mcolin           ###   ########.fr       */
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
	else if (key == KEY_W)
		mlx->key_tab[KEY_W_INDEX] = true;
	else if (key == KEY_S)
		mlx->key_tab[KEY_S_INDEX] = true;
	else if (key == KEY_F10)
		mlx->key_tab[KEY_F10_INDEX] = !mlx->key_tab[KEY_F10_INDEX];
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
