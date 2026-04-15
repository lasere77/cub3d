/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 08:43:02 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/15 15:08:47 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_MOVEMENT_BONUS_H
# define PLAYER_MOVEMENT_BONUS_H

# include "cub.h"

# define MOUSE_SPEED 750

void	get_mouse_track(t_mlx *mlx);
void	strafe_left(t_mlx *mlx);
void	strafe_right(t_mlx *mlx);

#endif