/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:32:13 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/13 14:32:04 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx_extended.h"
#include "player_movement.h"
#include "get_map.h"
#include "overlay.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void	calculate_data_dda(t_mlx *mlx, int mapX, int mapY)
{
	if (mlx->ray.ray_dir_x == 0)
		mlx->ray.delta_x = 1e30;
	else
		mlx->ray.delta_x = fabs(1 / mlx->ray.ray_dir_x);
	if (mlx->ray.ray_dir_y == 0)
		mlx->ray.delta_y = 1e30;
	else
		mlx->ray.delta_y = fabs(1 / mlx->ray.ray_dir_y);
	if (mlx->ray.ray_dir_x < 0)
		mlx->ray.side_x = (mlx->player.pos_x - mapX) * mlx->ray.delta_x;
	else
		mlx->ray.side_x = (mapX + 1 - mlx->player.pos_x) * mlx->ray.delta_x;
	if (mlx->ray.ray_dir_y < 0)
		mlx->ray.side_y = (mlx->player.pos_y - mapY) * mlx->ray.delta_y;
	else
		mlx->ray.side_y = (mapY + 1 - mlx->player.pos_y) * mlx->ray.delta_y;
}

int	dda(t_mlx *mlx, int *map_x, int *map_y)
{
	int	side;

	while (1)
	{
		if (mlx->ray.side_x < mlx->ray.side_y)
		{
			mlx->ray.side_x += mlx->ray.delta_x;
			*map_x += 1 - (2 * (mlx->ray.ray_dir_x < 0));
			side = 0;
		}
		else
		{
			mlx->ray.side_y += mlx->ray.delta_y;
			*map_y += 1 - (2 * (mlx->ray.ray_dir_y < 0));
			side = 1;
		}
		if (get_map_id(mlx, *map_x, *map_y) != MAP_ROOM)
			break ;
	}
	if (side == 0)
		mlx->ray.ray_dist = (mlx->ray.side_x - mlx->ray.delta_x);
	else
		mlx->ray.ray_dist = (mlx->ray.side_y - mlx->ray.delta_y);
	return (side);
}

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
	int		x;
	int		map_x;
	int		map_y;
	int		side;
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){DEAFAULT_COLOR});
	if (need_redraw(mlx))
	{
		mlx->screen.i = mlx->screen.h * mlx->screen.w;
		x = 0;
		while (x < mlx->screen.w)
		{
			mlx->ray.camera_x = 2 * x / (double)mlx->screen.w - 1;
			mlx->ray.ray_dir_x = mlx->player.plane_x * mlx->ray.camera_x;
			mlx->ray.ray_dir_x += mlx->player.dir_x;
			mlx->ray.ray_dir_y = mlx->player.plane_y * mlx->ray.camera_x;
			mlx->ray.ray_dir_y += mlx->player.dir_y;
			map_x = mlx->player.pos_x;
			map_y = mlx->player.pos_y;
			calculate_data_dda(mlx, map_x, map_y);
			side = dda(mlx, &map_x, &map_y);
			draw(mlx, mlx->screen.h, get_color(mlx, map_x, map_y, side));
			++x;
		}
		mlx_set_image_region(mlx->mlx, mlx->screen.img, 0, 0, mlx->screen.h, mlx->screen.w, mlx->screen.buffer);
	}
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win,  mlx->screen.img, (mlx->screen.w - mlx->screen.h) >> 1, -((mlx->screen.w - mlx->screen.h) >> 1), 1, 1, 90);
	if (mlx->key_tab[KEY_F10_INDEX])
		overlay(mlx);
	set_speed_from_frame_time(mlx);
	movement(mlx);
}
