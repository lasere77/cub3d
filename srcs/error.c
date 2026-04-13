/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:40:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/14 15:35:14 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void	destroy_txt(t_mlx *mlx)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (mlx->map.txt[i].img)
			mlx_destroy_image(mlx->mlx, mlx->map.txt[i].img);
		i++;
	}
}

static void	ft_free_42(t_mlx *mlx)
{
	size_t	i;

	free(mlx->screen.buffer_mini_map);
	free(mlx->screen.buffer);
	free(mlx->map.map);
	i = 0;
	while (i < 4)
		free(mlx->map.txt[i++].buffer);
}

void	panic(char *msg, t_mlx *mlx, int exit_code)
{
	if (msg || exit_code == -1)
		printf("Error\n%s\n", msg);
	if (exit_code == -1)
	{
		perror(NULL);
		exit_code = 1;
	}
	if (mlx)
	{
		destroy_txt(mlx);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->screen.buffer_mini_map)
			mlx_destroy_image(mlx->mlx, mlx->screen.img_mini_map);
		if (mlx->screen.img)
			mlx_destroy_image(mlx->mlx, mlx->screen.img);
		if (mlx->mlx)
			mlx_destroy_context(mlx->mlx);
		ft_free_42(mlx);
	}
	exit(exit_code);
}
