/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:25:34 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/13 10:55:34 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "error.h"
#include "get_next_line.h"
#include "libft.h"

#include <fcntl.h>

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
