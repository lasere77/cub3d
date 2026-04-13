/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:22:00 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/13 22:39:15 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_map.h"
#include "draw.h"

#include <math.h>

static void	calculate_data_dda(t_mlx *mlx)
{
	t_ray	*r;

	r = &mlx->ray;
	if (mlx->ray.ray_dir_x == 0)
		mlx->ray.delta_x = 1e30;
	else
		mlx->ray.delta_x = fabs(1 / mlx->ray.ray_dir_x);
	if (mlx->ray.ray_dir_y == 0)
		mlx->ray.delta_y = 1e30;
	else
		mlx->ray.delta_y = fabs(1 / mlx->ray.ray_dir_y);
	if (mlx->ray.ray_dir_x < 0)
		mlx->ray.side_x = (mlx->player.pos_x - mlx->map.map_x)
			* mlx->ray.delta_x;
	else
		mlx->ray.side_x = (mlx->map.map_x + 1.0 - mlx->player.pos_x)
			* mlx->ray.delta_x;
	if (mlx->ray.ray_dir_y < 0)
		mlx->ray.side_y = (mlx->player.pos_y - mlx->map.map_y)
			* mlx->ray.delta_y;
	else
		mlx->ray.side_y = (mlx->map.map_y + 1.0 - mlx->player.pos_y)
			* mlx->ray.delta_y;
}

static int	get_side(t_mlx *mlx)
{
	int	side;

	while (1)
	{
		if (mlx->ray.side_x < mlx->ray.side_y)
		{
			mlx->ray.side_x += mlx->ray.delta_x;
			mlx->map.map_x += 1 - (2 * (mlx->ray.ray_dir_x < 0));
			side = 0;
		}
		else
		{
			mlx->ray.side_y += mlx->ray.delta_y;
			mlx->map.map_y += 1 - (2 * (mlx->ray.ray_dir_y < 0));
			side = 1;
		}
		if (get_map_id(mlx, mlx->map.map_x, mlx->map.map_y) != MAP_ROOM)
			break ;
	}
	if (side == 0)
		mlx->ray.ray_dist = (mlx->ray.side_x - mlx->ray.delta_x);
	else
		mlx->ray.ray_dist = (mlx->ray.side_y - mlx->ray.delta_y);
	return (side);
}

void	dda(t_mlx *mlx)
{
	int	x;
	int	side;

	x = 0;
	while (x < mlx->screen.w)
	{
		mlx->ray.camera_x = 2 * x / (double)mlx->screen.w - 1;
		mlx->ray.ray_dir_x = mlx->player.plane_x * mlx->ray.camera_x;
		mlx->ray.ray_dir_x += mlx->player.dir_x;
		mlx->ray.ray_dir_y = mlx->player.plane_y * mlx->ray.camera_x;
		mlx->ray.ray_dir_y += mlx->player.dir_y;
		mlx->map.map_x = mlx->player.pos_x;
		mlx->map.map_y = mlx->player.pos_y;
		calculate_data_dda(mlx);
		side = get_side(mlx);
		draw(mlx, mlx->screen.h, side);
		++x;
	}
}
