/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:42:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/15 16:49:44 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "raycasting.h"
#include "event.h"
#include "error.h"
#include "init_mlx.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc != 2)
		panic("Format: ./cub3D your_scene_description.cub", NULL, 1);
	mlx = (t_mlx){0};
	mlx.ray = (t_ray){0};
	init_mlx(&mlx, argv[1]);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook_down, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYUP, key_hook_up, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, window_hook, &mlx);
	gettimeofday(&mlx.start, NULL);
	mlx_add_loop_hook(mlx.mlx, update, &mlx);
	mlx_loop(mlx.mlx);
	panic(NULL, &mlx, 0);
}
