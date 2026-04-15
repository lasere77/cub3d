/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:10:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/15 09:00:00 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_MOVEMENT_H
# define PLAYER_MOVEMENT_H

# include "cub.h"

void	movement(t_mlx *mlx);
void	left_rotation(t_mlx *mlx);
void	right_rotation(t_mlx *mlx);

#endif