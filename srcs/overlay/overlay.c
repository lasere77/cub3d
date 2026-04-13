/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:16:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/14 15:47:42 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlay.h"
#include "libft.h"
#include "mlx_extended.h"

static void	display_fps(t_mlx *mlx)
{
	struct timeval	current;
	int				current_time;
	char			buffer[(sizeof(MSG_MLX_FPS) - 1) + 13];

	gettimeofday(&current, NULL);
	current_time = current.tv_sec + current.tv_usec / 100000;
	if (current_time - mlx->screen.wait_second)
	{
		mlx->screen.wait_second = current_time;
		mlx->mlx_fps = 1 / mlx->frame_time;
	}
	ft_strcpy(buffer, MSG_MLX_FPS);
	ft_itoa_buffer(mlx->mlx_fps, buffer + (sizeof(MSG_MLX_FPS) - 1), 13);
	mlx_string_put(mlx->mlx, mlx->win, 20, 20,
		(mlx_color){.rgba = 0xFF}, buffer);
}

static void	display_player_pos(t_mlx *mlx)
{
	char	str_player_pos_x[(sizeof(MSG_PLAYER_POS_X) - 1) + 13];
	char	str_player_pos_y[(sizeof(MSG_PLAYER_POS_Y) - 1) + 13];

	ft_strcpy(str_player_pos_x, MSG_PLAYER_POS_X);
	ft_strcpy(str_player_pos_y, MSG_PLAYER_POS_Y);
	ft_itoa_buffer(mlx->player.pos_x,
		str_player_pos_x + (sizeof(MSG_PLAYER_POS_X) - 1), 13);
	ft_itoa_buffer(mlx->player.pos_y,
		str_player_pos_y + (sizeof(MSG_PLAYER_POS_Y) - 1), 13);
	mlx_string_put(mlx->mlx, mlx->win, 20, 40,
		(mlx_color){.rgba = 0xFF}, str_player_pos_x);
	mlx_string_put(mlx->mlx, mlx->win, 20, 60,
		(mlx_color){.rgba = 0xFF}, str_player_pos_y);
}

void	overlay(t_mlx *mlx)
{
	display_fps(mlx);
	display_player_pos(mlx);
	mlx_put_transformed_image_to_window(mlx->mlx, mlx->win,
		mlx->screen.img_mini_map,
		mlx->screen.w - (mlx->map.w * MINI_MAP_SIZE), 0,
		MINI_MAP_SIZE, MINI_MAP_SIZE, 0);
}
