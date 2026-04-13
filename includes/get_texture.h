/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:37:22 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/13 22:33:11 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_TEXTURE_H
# define GET_TEXTURE_H

# include "cub.h"

typedef enum e_side
{
	SIDE_NO,
	SIDE_SO,
	SIDE_WE,
	SIDE_EA
}		t_side;

void	get_texture(t_mlx *mlx, char **scene);

#endif