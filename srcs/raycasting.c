/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:32:13 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/08 11:20:12 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_data_dda(t_mlx *mlx, int mapX, int mapY)
{
	if (mlx->ray.ray_dir_x == 0)
		mlx->ray.delta_x = 1e30;
	else
		mlx->ray.delta_x = D_ABS(1 / mlx->ray.ray_dir_x);
	if (mlx->ray.ray_dir_y == 0)
		mlx->ray.delta_y = 1e30;
	else
		mlx->ray.delta_y = D_ABS(1 / mlx->ray.ray_dir_y);
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

void	update(void *param)
{
	int		x;
	int		map_x;
	int		map_y;
	int		side;
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_get_window_size(mlx->mlx, mlx->win, &mlx->screen.w, &mlx->screen.h);
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
}
