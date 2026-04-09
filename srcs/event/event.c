/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:47:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/09 10:45:02 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

void	key_hook(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	if (key == 41)
		mlx_loop_end(mlx->mlx);
	if (key == 68)
		mlx_set_window_fullscreen(mlx->mlx, mlx->win, 1);
	if (key == 69)
		mlx_set_window_fullscreen(mlx->mlx, mlx->win, 0);
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end(((t_mlx *)param)->mlx);
}
