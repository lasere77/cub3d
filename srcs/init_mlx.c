/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:46:07 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/12 12:14:16 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "error.h"
#include "mlx.h"
#include "libft.h"
#include "get_scene.h"
#include "get_ceil_floor.h"
#include "get_map.h"

static void	init_window(t_mlx *mlx)
{
	mlx_window_create_info	info;

	info = (mlx_window_create_info){0};
	info.title = "cub3D";
	info.is_resizable = false;
	info.is_fullscreen = true;
	mlx->win = mlx_new_window(mlx->mlx, &info);
	if (!mlx->win)
		panic("Error creating windows.", mlx, 1);
	mlx_get_screen_size(mlx->mlx, mlx->win, &mlx->screen.w, &mlx->screen.h);
	mlx_set_window_size(mlx->mlx, mlx->win, mlx->screen.w, mlx->screen.h);
	mlx->screen.buffer = malloc(sizeof(mlx_color) * mlx->screen.w * mlx->screen.h);
	if (!mlx->screen.buffer)
		panic("Memory alloc failed.\n", mlx, 1);
	mlx->screen.img = mlx_new_image(mlx->mlx, mlx->screen.h, mlx->screen.w);
	if (!mlx->screen.img)
		panic("Error creating image.", mlx, 1);
	mlx->screen.need_redraw = true;
}

void	init_mlx(t_mlx *mlx, char *argv)
{
	char	**scene;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		panic("Failed to load MacroLibX.", NULL, 1);
	mlx_set_fps_goal(mlx->mlx, FPS_GOAL);
	scene = get_scene(mlx, argv);
	get_texture(mlx, scene);
	get_ceil_floor(mlx, scene);
	get_map(mlx, scene);
	ft_free_split(scene);
	init_window(mlx);
}
