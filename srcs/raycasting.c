/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:32:13 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/11 09:52:58 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx_extended.h"
#include "player_movement.h"

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

int	dda(t_mlx *mlx, int *mapX, int *mapY)
{
	int	side;

	while (1)
	{
		if (mlx->ray.side_x < mlx->ray.side_y)
		{
			mlx->ray.side_x += mlx->ray.delta_x;
			*mapX += 1 - (2 * (mlx->ray.ray_dir_x < 0));
			side = 0;
		}
		else
		{
			mlx->ray.side_y += mlx->ray.delta_y;
			*mapY += 1 - (2 * (mlx->ray.ray_dir_y < 0));
			side = 1;
		}
		if (worldMap[*mapX][*mapY] > 0)
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
	mlx->player.move_speed = mlx->frame_time * 5.0;
    mlx->player.rot_speed = mlx->frame_time * 3.0;
}

void	update(void *param)
{
	int		x;
	int		map_x;
	int		map_y;
	int		side;
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx->screen.need_redraw)
	{
		mlx_set_image_region(mlx->mlx, mlx->screen.img, 0, 0, mlx->screen.w, mlx->screen.h, mlx->screen.wallpaper);
		mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0x334D4DFF});
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
			draw(mlx, x, mlx->screen.h, get_color(map_x, map_y, side));
			x++;
		}
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen.img, 0, 0);	
		mlx->screen.need_redraw = false;
	}
	set_speed_from_frame_time(mlx);
	movement(mlx);
}
