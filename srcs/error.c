/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:40:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/11 15:57:54 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub.h"

#include <stdio.h>
#include <stdlib.h>

void	destroy_txt(t_mlx *mlx)
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
		if (mlx->screen.img)
			mlx_destroy_image(mlx->mlx, mlx->screen.img);
		if (mlx->mlx)
			mlx_destroy_context(mlx->mlx);
		free(mlx->screen.color_tab);
		free(mlx->screen.wallpaper);
		free(mlx->map.map);
	}
	exit(exit_code);
}
