/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 10:34:26 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/08 10:38:11 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub.h"

void	calculate_data_dda(t_mlx *mlx, int mapX, int mapY);
int		dda(t_mlx *mlx, int *mapX, int *mapY);
void	update(void *param);

#endif