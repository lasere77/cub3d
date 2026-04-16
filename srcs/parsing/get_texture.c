/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:37:03 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/16 20:28:54 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "error.h"
#include "get_texture.h"
#include "libft.h"
#include "mlx_extended.h"

static void	set_texture_buffer(t_mlx *mlx, char **scene, t_side side)
{
	t_txt		*txt;
	mlx_color	*buffer;

	txt = &mlx->map.txt[side];
	buffer = malloc(sizeof(mlx_color) * txt->w * txt->h);
	if (!buffer)
	{
		ft_free_split(scene);
		panic("Memory alloc failed.", mlx, 1);
	}
	mlx_get_image_region(mlx->mlx, txt->img, 0, 0, txt->w, txt->h, buffer);
	mlx->map.txt[side].buffer = buffer;
}

static char	*get_path(t_mlx *mlx, char **scene, int i)
{
	int		start;
	int		end;
	char	*path;

	start = 2;
	while (scene[i][start] == ' ')
		start++;
	end = start;
	while (scene[i][end] && scene[i][end] != '\n')
		end++;
	if (end == start)
	{
		ft_free_split(scene);
		panic("Texture's path not valid", mlx, 1);
	}
	path = ft_substr(scene[i], start, end - start);
	if (!path)
	{
		ft_free_split(scene);
		panic("Memory alloc failed.", mlx, 1);
	}
	return (path);
}

static void	set_texture(t_mlx *mlx, char **scene, int i, t_side side)
{
	char	*path;

	if (mlx->map.txt[side].is_valid)
	{
		ft_free_split(scene);
		panic("Wrong map format, double element", mlx, 1);
	}
	mlx->map.txt[side].is_valid = 1;
	path = get_path(mlx, scene, i);
	mlx->map.txt[side].img = mlx_new_image_from_file(mlx->mlx, path,
			&mlx->map.txt[side].w, &mlx->map.txt[side].h);
	free(path);
	if (!mlx->map.txt[side].img)
	{
		ft_free_split(scene);
		panic("Wrong texture", mlx, 1);
	}
	scene[i][0] = '\n';
	set_texture_buffer(mlx, scene, side);
}

void	get_texture(t_mlx *mlx, char **scene)
{
	int	i;

	i = 0;
	while (scene[i])
	{
		if (ft_strncmp(scene[i], "NO ", 3) == 0)
			set_texture(mlx, scene, i, SIDE_NO);
		if (ft_strncmp(scene[i], "SO ", 3) == 0)
			set_texture(mlx, scene, i, SIDE_SO);
		if (ft_strncmp(scene[i], "WE ", 3) == 0)
			set_texture(mlx, scene, i, SIDE_WE);
		if (ft_strncmp(scene[i], "EA ", 3) == 0)
			set_texture(mlx, scene, i, SIDE_EA);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (mlx->map.txt[i].is_valid == 0)
		{
			ft_free_split(scene);
			panic("Wrong map, miss element", mlx, 1);
		}
		i++;
	}
}
