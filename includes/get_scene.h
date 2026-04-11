/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:26:09 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/11 10:41:02 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_SCENE_H
# define GET_SCENE_H

# include "cub.h"

typedef enum e_side
{
	SIDE_NO,
	SIDE_SO,
	SIDE_WE,
	SIDE_EA
}		t_side;

char	**get_scene(t_mlx *mlx, char *argv);
void	get_texture(t_mlx *mlx, char **scene);

#endif