/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:56:31 by mcolin            #+#    #+#             */
/*   Updated: 2026/04/09 17:59:00 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# define KEY_ESC 41
# define KEY_F11 68
# define KEY_F12 69
# define KEY_A 4
# define KEY_W 26
# define KEY_S 22
# define KEY_D 7

void	key_hook(int key, void *param);
void	window_hook(int event, void *param);

#endif