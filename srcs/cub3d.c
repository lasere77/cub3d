/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:42:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/08 11:17:42 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "cub.h"
#include "raycasting.h"
#include "event.h"
#include "error.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int	worldMap[MAP_WIDTH][MAPHEIGHT] =
{
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static void	check_resolution(t_mlx *mlx)
{
	int	h;
	int	w;

	mlx_get_window_size(mlx->mlx, mlx->win, &w, &h);
	if (w != mlx->screen.w || h != mlx->screen.h || !mlx->screen.img)
	{
		mlx->screen.h = h;
		mlx->screen.w = w;
		if (mlx->screen.img)
			mlx_destroy_image(mlx->mlx, mlx->screen.img);
		mlx->screen.img = mlx_new_image(mlx->mlx, w, h);
		if (!mlx->screen.img)
			panic("Error creating image.", mlx, 1);
		printf("resize\n");
		}
}

void	draw(t_mlx *mlx, int x, int h, mlx_color color)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = h / mlx->ray.ray_dist;
	draw_start = -line_height / 2 + h / 2;
	draw_end = line_height / 2 + h / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= h)
		draw_end = h - 1;
	check_resolution(mlx);
	while (draw_start < draw_end)
		mlx_set_image_pixel(mlx->mlx, mlx->screen.img, x, draw_start++, color);
	mlx_clear_window(mlx->mlx, mlx->win, (mlx_color){.rgba = 0x334D4DFF});
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen.img, 0, 0);
}

mlx_color	get_color(int mapX, int mapY, int side)
{
	mlx_color	color;

	color = (mlx_color){0};
	color.a = ALPHA;
	if (worldMap[mapX][mapY] == 1)
		color.r = 255;
	else if (worldMap[mapX][mapY] == 2)
		color.g = 255;
	else if (worldMap[mapX][mapY] == 3)
		color.b = 255;
	else if (worldMap[mapX][mapY] == 4)
		color.rgba = 255 << 16 | 255 << 8 | 255;
	else
		color.rgba = 255 << 16 | 150 << 8 | 20;
	if (side == 1)
		color.rgba = color.rgba / 2;
	return (color);
}

static inline void	init_window(t_mlx *mlx)
{
	mlx_window_create_info	info;

	info = (mlx_window_create_info){0};
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		panic("Failed to load MacroLibX.", NULL, 1);
	info.title = "cub3D";
	info.is_resizable = true;
	info.height = 1080;
	info.width = 1920;
	mlx->win = mlx_new_window(mlx->mlx, &info);
	if (!mlx->win)
		panic("Error creating windows.", mlx, 1);
	mlx_get_window_size(mlx->mlx, mlx->win, &mlx->screen.w, &mlx->screen.h);
}

int	main(void)
{
	t_mlx		mlx;

	mlx = (t_mlx){0};
	mlx.player = (t_player){22, 12, -1, 0, 0, 0.66};
	mlx.ray = (t_ray){0};
	init_window(&mlx);
	mlx_set_fps_goal(mlx.mlx, FPS_GOAL);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
	gettimeofday(&mlx.start, NULL);
	mlx_add_loop_hook(mlx.mlx, update, &mlx);
	mlx_loop(mlx.mlx);
	panic(NULL, &mlx, 0);
}
