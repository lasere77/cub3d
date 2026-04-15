/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:06:11 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/15 16:18:10 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_MAP_H
# define GET_MAP_H

# include "cub.h"

# define MAP_IDENTIFIERS "01NSWE "
# define MAP_ERROR "Map have to be the last part and identifiers are \
0, 1, N, S, W, E"

typedef enum e_mapid
{
	MAP_ROOM,
	MAP_WALL,
	MAP_VOID
}		t_mapid;

void	get_map(t_mlx *mlx, char **scene);
t_mapid	get_map_id(t_mlx *mlx, size_t w, size_t h);

#endif