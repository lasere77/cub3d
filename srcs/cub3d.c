/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:42:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/12 12:11:39 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_extended.h"

#include "cub.h"
#include "raycasting.h"
#include "event.h"
#include "error.h"
#include "init_mlx.h"
#include "get_map.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void	draw(t_mlx *mlx, int h, mlx_color color)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			i;

	line_height = h / mlx->ray.ray_dist;
	draw_start = (-line_height >> 1) + (h >> 1);
	draw_end = (line_height >> 1) + (h >> 1);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= h)
		draw_end = h - 1;
	i = 0;
	mlx->screen.i -= mlx->screen.h;
	while (i < draw_start)
		mlx->screen.buffer[mlx->screen.i + i++] = mlx->map.ceil;
	while (i < draw_end)
		mlx->screen.buffer[mlx->screen.i + i++] = color;
	while (i < mlx->screen.h)
		mlx->screen.buffer[mlx->screen.i + i++] = mlx->map.floor;
}

mlx_color	get_color(t_mlx *mlx, int map_x, int map_y, int side)
{
	mlx_color	color;

	color = (mlx_color){0};
	color.a = ALPHA;
	if (get_map_id(mlx, map_x, map_y) == MAP_WALL)
		color.r = 255;
	if (side == 1/* && worldMap[mapX][mapY] != 1*/)
		color.rgba = color.rgba / 2;
	return (color);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
		panic("Format: ./cub3D your_scene_description.cub", NULL, 1);
	mlx = (t_mlx){0};
	mlx.ray = (t_ray){0};
	init_mlx(&mlx, argv[1]);
	for (size_t h = 0; h < mlx.map.h; h++)
	{
		for (size_t w = 0; w < mlx.map.w; w++)
		{
			if (get_map_id(&mlx, w, h) == MAP_VOID)
				printf(" ");
			else
				printf("%d", get_map_id(&mlx, w, h));
		}
		printf("\n");
	}
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook_down, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYUP, key_hook_up, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
	gettimeofday(&mlx.start, NULL);
	mlx_add_loop_hook(mlx.mlx, update, &mlx);
	mlx_loop(mlx.mlx);
	panic(NULL, &mlx, 0);
}
	// mlx_set_image_region(mlx->mlx, mlx->screen.img, x, draw_start, 1, draw_end - draw_start, mlx->screen.color_tab);