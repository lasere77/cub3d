/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:21:09 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/15 11:40:19 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OVERLAY_H
# define OVERLAY_H

# include "cub.h"

# define MSG_MLX_FPS "mlx fps:"

# define MSG_PLAYER_POS_X "player x:"

# define MSG_PLAYER_POS_Y "player y:"

void	overlay(t_mlx *mlx);

#endif