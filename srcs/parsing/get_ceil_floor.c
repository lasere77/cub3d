/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceil_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:38:23 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/12 16:56:33 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "error.h"
#include "get_ceil_floor.h"
#include "libft.h"

static int	check_color(char *scene, int *color)
{
	char	number[4];
	size_t	size;
	int		rgb;
	int		i;

	rgb = -1;
	while (++rgb < RGB_SIZE)
	{
		ft_bzero(number, 4);
		size = 0;
		while (ft_isdigit(scene[size]))
			size++;
		if (!size || size > 3)
			return (1);
		i = size;
		while (size--)
			number[size] = scene[size];
		color[rgb] = ft_atoi(number);
		if (color[rgb] > 255)
			return (1);
		if ((rgb < 2 && scene[i] != ',') || (rgb == 2 && scene[i] != '\n'))
			return (1);
		scene += i + 1;
	}
	return (0);
}

static int	get_rgba(t_mlx *mlx, char *scene, char type)
{
	int			rgb[RGB_SIZE];
	mlx_color	color;

	if (check_color(scene, rgb))
		return (1);
	color.a = ALPHA;
	color.r = rgb[RGB_R];
	color.g = rgb[RGB_G];
	color.b = rgb[RGB_B];
	if (type == 'F')
		mlx->map.floor = color;
	else
		mlx->map.ceil = color;
	return (0);
}

static int	set_ceil_floor(t_mlx *mlx, char *scene, char type,
		int *done)
{
	int	i;

	if (*done == 1)
	{
		*done = 0;
		return (1);
	}
	i = 1;
	while (scene[i] == ' ')
		i++;
	if (get_rgba(mlx, &scene[i], type))
		return (1);
	*scene = '\n';
	*done = 1;
	return (0);
}

void	get_ceil_floor(t_mlx *mlx, char **scene)
{
	int	i;
	int	ceil_done;
	int	floor_done;

	i = 0;
	ceil_done = 0;
	floor_done = 0;
	while (scene[i])
	{
		if (ft_strncmp(scene[i], "F ", 2) == 0
			&& set_ceil_floor(mlx, scene[i], 'F', &floor_done))
			break ;
		if (ft_strncmp(scene[i], "C ", 2) == 0
			&& set_ceil_floor(mlx, scene[i], 'C', &ceil_done))
			break ;
		i++;
	}
	if (!ceil_done || !floor_done)
	{
		ft_free_split(scene);
		panic(FLOOR_CEILING_ERROR, mlx, 1);
	}
}
