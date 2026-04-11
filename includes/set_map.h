/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:09:57 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/11 16:30:20 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_MAP_H
# define SET_MAP_H

# include "cub.h"

# define PLAYER_DIR "NSWE"

int		set_map(t_mlx *mlx, char **scene, int i);
bool	get_player(t_mlx *mlx, char **scene);

#endif