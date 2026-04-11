/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:25:34 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/11 16:25:53 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "error.h"
#include "get_next_line.h"
#include "get_scene.h"
#include "libft.h"
#include <fcntl.h>

static char	*get_path(t_mlx *mlx, char **scene, int i)
{
	int		start;
	int		end;
	char	*path;

	start = 2;
	while (scene[i][start] == ' ')
		start++;
	end = start;
	while (scene[i][end] && scene[i][end] != ' ' && scene[i][end] != '\n')
		end++;
	if (end == start)
	{
		ft_free_split(scene);
		panic("Texture's path empty", mlx, 1);
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

static char	**get_file_content(t_mlx *mlx, char *argv, int size)
{
	char	**scene;
	char	*temp;
	int		fd;
	int		i;

	scene = ft_calloc(size + 1, sizeof(char *));
	if (!scene)
		panic("Memory alloc failed.", mlx, 1);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free(scene);
		panic(NULL, mlx, -1);
	}
	i = 0;
	while (1)
	{
		temp = get_next_line(fd, "\n");
		if (!temp)
			break ;
		scene[i] = temp;
		i++;
	}
	return (scene);
}

char	**get_scene(t_mlx *mlx, char *argv)
{
	size_t	size;
	char	**scene;
	ssize_t	nb_lines;

	size = ft_strlen(argv);
	if (size < 5 || ft_strcmp(&argv[size - 4], ".cub"))
		panic("Please enter a valid .cub scene", NULL, 1);
	nb_lines = get_number_line_file(argv, "\n");
	if (nb_lines == -1)
		panic(NULL, mlx, -1);
	if (nb_lines == 0)
		panic("Your scene file is empty", mlx, 1);
	scene = get_file_content(mlx, argv, nb_lines);
	return (scene);
}
