/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:32:13 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/14 15:45:40 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx_extended.h"
#include "player_movement.h"
#include "overlay.h"
#include "dda.h"

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
	// struct timeval	current;
	// double			current_time;

	if (mlx->screen.need_redraw == false)
		return (false);
	// gettimeofday(&current, NULL);
	// current_time = current.tv_sec + current.tv_usec / 1000000.0;
	// if ((current_time - mlx->screen.last_update) < 1 / REAL_FPS_GOAL)
		// return (false);
	// mlx->screen.last_update = current_time;
	mlx->screen.need_redraw = false;
	return (true);
}

static void	draw_mini_map(t_mlx *mlx)
{
	size_t	index;

	index = 0;
	while (index < mlx->map.w * mlx->map.h)
	{
		if (mlx->map.map[index] == '0')
			mlx->screen.buffer_mini_map[index] = (mlx_color)
			{.rgba = 0xFFFFFFFF};
		else if (mlx->map.map[index] == '1')
			mlx->screen.buffer_mini_map[index] = (mlx_color)
			{.rgba = 0xFF00FF};
		++index;
	}
	mlx->screen.buffer_mini_map[(int)mlx->player.pos_y * mlx->map.w
		+ (int)mlx->player.pos_x] = (mlx_color){.rgba = 0xFF0000FF};
	mlx_set_image_region(mlx->mlx, mlx->screen.img_mini_map, 0, 0, mlx->map.w,
		mlx->map.h, mlx->screen.buffer_mini_map);
}

void	update(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0xFF});
	if (need_redraw(mlx))
	{
		mlx->screen.i = mlx->screen.h * mlx->screen.w;
		mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0x334D4DFF});
		dda(mlx);
		mlx_set_image_region(mlx->mlx, mlx->screen.img, 0, 0,
			mlx->screen.h, mlx->screen.w, mlx->screen.buffer);
		draw_mini_map(mlx);
	}
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win, mlx->screen.img,
		(mlx->screen.w - mlx->screen.h) >> 1,
		-((mlx->screen.w - mlx->screen.h) >> 1), 1, 1, 90);
	if (mlx->key_tab[KEY_F10_INDEX])
		overlay(mlx);
	set_speed_from_frame_time(mlx);
	movement(mlx);
}
