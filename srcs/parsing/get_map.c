/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:05:45 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/15 17:06:39 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "error.h"
#include "get_map.h"
#include "libft.h"
#include "set_map.h"

#include <stddef.h>
#include <stdio.h>

t_mapid	get_map_id(t_mlx *mlx, size_t w, size_t h)
{
	int	index;

	if (mlx->map.w < w || w < 0 || mlx->map.h < h || h < 0)
		return (MAP_VOID);
	index = h * mlx->map.w + w;
	if (mlx->map.map[index] == '0')
		return (MAP_ROOM);
	else if (mlx->map.map[index] == '1')
		return (MAP_WALL);
	else
		return (MAP_VOID);
}

static void	init_map_free42(t_mlx *mlx, char **free42)
{
	mlx->map.map = malloc(sizeof(char) * (mlx->map.w * mlx->map.h + 1));
	if (!mlx->map.map)
	{
		ft_free_split(free42);
		panic("Memory alloc failed.", mlx, 1);
	}
	ft_memset(mlx->map.map, '2', mlx->map.w * mlx->map.h);
}

static int	linelen(char *scene)
{
	int	size;

	size = 0;
	while (scene[size] && ft_strchr(MAP_IDENTIFIERS, scene[size]))
		size++;
	if (scene[size] && scene[size] != '\n' && scene[size] != EOF)
		return (0);
	return (size);
}

static int	get_map_size(t_mlx *mlx, char **scene, int i)
{
	int	w;
	int	max_w;
	int	h;

	h = 0;
	max_w = 0;
	while (scene[i + h] && *scene[i + h] && *scene[i + h] != '\n')
	{
		w = linelen(scene[i + h]);
		if (w == 0)
			return (1);
		if (max_w < w)
			max_w = w;
		h++;
	}
	if (h == 0 || (scene[i + h] && *scene[i + h]))
		return (1);
	mlx->map.h = h;
	mlx->map.w = max_w;
	return (0);
}

void	get_map(t_mlx *mlx, char **scene)
{
	int	i;

	i = 0;
	while (scene[i] && *scene[i] == '\n')
		i++;
	if (get_map_size(mlx, scene, i))
	{
		ft_free_split(scene);
		panic(MAP_ERROR, mlx, 1);
	}
	if (get_player(mlx, &scene[i]))
	{
		ft_free_split(scene);
		panic("Map need one player", mlx, 1);
	}
	init_map_free42(mlx, scene);
	if (set_map(mlx, scene, i))
	{
		ft_free_split(scene);
		panic("Map need to be closed", mlx, 1);
	}
}
