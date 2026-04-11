/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:09:34 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/11 16:30:55 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "set_map.h"
#include "get_map.h"

static void	set_player(t_mlx *mlx, int x, int y, char dir)
{
	mlx->player.pos_x = x;
	mlx->player.pos_y = y;
	if (dir == 'N' || dir == 'S')
		mlx->player.dir_x = 0;
	else if (dir == 'W')
		mlx->player.dir_x = 1;
	else if (dir == 'E')
		mlx->player.dir_x = -1;
	if (dir == 'W' || dir == 'E')
		mlx->player.dir_y = 0;
	else if (dir == 'N')
		mlx->player.dir_y = -1;
	else if (dir == 'S')
		mlx->player.dir_y = 1;
	mlx->player.plane_x = 0.66;
	mlx->player.plane_y = 0;
}

bool	get_player(t_mlx *mlx, char **scene)
{
	size_t	y;
	size_t	x;
	bool	have_player;

	y = 0;
	have_player = 0;
	while (y < mlx->map.h)
	{
		x = 0;
		while (scene[y][x] && scene[y][x] != '\n')
		{
			if (ft_strchr(PLAYER_DIR, scene[y][x]))
			{
				if (have_player)
					return (1);
				set_player(mlx, x, y, scene[y][x]);
				scene[y][x] = '0';
				have_player = 1;
			}
			x++;
		}
		y++;
	}
	return (!have_player);
}

static int	check_map(t_mlx *mlx)
{
	size_t	h;
	size_t	w;

	h = -1;
	while (++h < mlx->map.h)
	{
		w = -1;
		while (++w < mlx->map.w)
		{
			if (get_map_id(mlx, w, h) != MAP_ROOM)
				continue ;
			if (get_map_id(mlx, w, h - 1) == MAP_VOID)
				return (1);
			if (get_map_id(mlx, w + 1, h) == MAP_VOID)
				return (1);
			if (get_map_id(mlx, w, h + 1) == MAP_VOID)
				return (1);
			if (get_map_id(mlx, w - 1, h) == MAP_VOID)
				return (1);
		}
	}
	return (0);
}

int	set_map(t_mlx *mlx, char **scene, int i)
{
	size_t	y;
	size_t	x;
	size_t	j;

	x = 0;
	y = -1;
	j = 0;
	while (++y < mlx->map.h)
	{
		x = 0;
		while (x < mlx->map.w && scene[i + y][x])
		{
			if (scene[i + y][x] == '1')
				mlx->map.map[j] = '1';
			else if (scene[i + y][x] == '0')
				mlx->map.map[j] = '0';
			x++;
			j++;
		}
		while (x++ < mlx->map.w)
			j++;
	}
	if (check_map(mlx))
		return (1);
	return (0);
}
