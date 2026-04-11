/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceil_floor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:39:54 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/11 14:58:22 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CEIL_FLOOR_H
# define GET_CEIL_FLOOR_H

# include "cub.h"

# define FLOOR_CEILING_ERROR "Map need one floor and one ceiling \
color: R,G,B in range [0,255]: 0, 255, 255"

typedef enum e_rgb
{
	RGB_R,
	RGB_G,
	RGB_B,
	RGB_SIZE
}		t_rgb;

void	get_ceil_floor(t_mlx *mlx, char **scene);

#endif