/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:10:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/10 16:12:09 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_MOVEMENT_H
# define PLAYER_MOVEMENT_H

#include "cub.h"

void	left_rotation(t_mlx *mlx);
void	right_rotation(t_mlx *mlx);
void 	move_forward(t_mlx *mlx);
void 	move_backward(t_mlx *mlx);

#endif