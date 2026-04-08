/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:40:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/08 17:12:04 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub.h"

#include <stdio.h>
#include <stdlib.h>

void	panic(char *msg, t_mlx *mlx, int exit_code)
{
	if (msg)
		printf("Error\n%s\n", msg);
	if (mlx)
	{
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->screen.img)
			mlx_destroy_image(mlx->mlx, mlx->screen.img);
		if (mlx->mlx)
			mlx_destroy_context(mlx->mlx);
	}
	exit(exit_code);
}
