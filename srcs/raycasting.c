/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:32:13 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/13 22:38:46 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_map.h"
#include "mlx_extended.h"
#include "player_movement.h"
#include "dda.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static void	set_speed_from_frame_time(t_mlx *mlx)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	mlx->frame_time = end.tv_sec * 1000 + end.tv_usec / 1000.0;
	mlx->frame_time -= mlx->start.tv_sec * 1000 + mlx->start.tv_usec / 1000.0;
	mlx->frame_time /= 1000;
	gettimeofday(&mlx->start, NULL);
	mlx->player.move_speed = mlx->frame_time * 4.0;
	mlx->player.rot_speed = mlx->frame_time * 2.0;
}

static bool	need_redraw(t_mlx *mlx)
{
	struct timeval	current;
	double			current_time;

	if (mlx->screen.need_redraw == false)
		return (false);
	gettimeofday(&current, NULL);
	current_time = current.tv_sec + current.tv_usec / 1000000.0;
	if ((current_time - mlx->screen.last_update) < 1 / REAL_FPS_GOAL)
		return (false);
	mlx->screen.last_update = current_time;
	mlx->screen.need_redraw = false;
	return (true);
}

void	update(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (need_redraw(mlx))
	{
		mlx->screen.i = mlx->screen.h * mlx->screen.w;
		mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0x334D4DFF});
		dda(mlx);
		mlx_set_image_region(mlx->mlx, mlx->screen.img, 0, 0, mlx->screen.h,
			mlx->screen.w, mlx->screen.buffer);
		mlx_put_transformed_image_to_window(mlx->mlx, mlx->win, mlx->screen.img,
			(mlx->screen.w - mlx->screen.h) >> 1, -((mlx->screen.w
					- mlx->screen.h) >> 1), 1, 1, 90);
	}
	set_speed_from_frame_time(mlx);
	movement(mlx);
}
