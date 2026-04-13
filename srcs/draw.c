/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:27:39 by ykolacze          #+#    #+#             */
/*   Updated: 2026/04/13 22:39:39 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_texture.h"

#include <math.h>

static void	put_color(t_mlx *mlx, t_side side)
{
	t_ray	*r;
	t_txt	*txt;
	double	step;
	double	row;
	int		i;

	r = &mlx->ray;
	txt = &mlx->map.txt[side];
	i = fmax(r->draw_start, 0);
	step = (double)txt->h / r->line_height;
	row = -fmin(r->draw_start, 0) * step;
	while (i < r->draw_end)
	{
		mlx->screen.buffer[mlx->screen.i + i] = txt->buffer[(int)row * txt->w
			+ r->txt_x];
		row += step;
		i++;
	}
}

static void	draw_texture(t_mlx *mlx, int side)
{
	t_ray	*ray;
	t_side	txt_side;
	double	wall_x;

	ray = &mlx->ray;
	if (side == 0 && ray->ray_dir_x > 0)
		txt_side = SIDE_EA;
	if (side == 0 && ray->ray_dir_x < 0)
		txt_side = SIDE_WE;
	if (side == 1 && ray->ray_dir_y > 0)
		txt_side = SIDE_NO;
	if (side == 1 && ray->ray_dir_y < 0)
		txt_side = SIDE_SO;
	if (side == 0)
		wall_x = mlx->player.pos_y + ray->ray_dist * ray->ray_dir_y;
	else
		wall_x = mlx->player.pos_x + ray->ray_dist * ray->ray_dir_x;
	wall_x -= floor((wall_x));
	ray->txt_x = (int)(wall_x * (double)(mlx->map.txt[txt_side].w));
	if (side == 0 && ray->ray_dir_x < 0)
		ray->txt_x = mlx->map.txt[txt_side].w - ray->txt_x - 1;
	if (side == 1 && ray->ray_dir_y > 0)
		ray->txt_x = mlx->map.txt[txt_side].w - ray->txt_x - 1;
	put_color(mlx, txt_side);
}

void	draw(t_mlx *mlx, int h, int side)
{
	int	i;

	mlx->ray.line_height = h / mlx->ray.ray_dist;
	mlx->ray.draw_start = (-mlx->ray.line_height >> 1) + (h >> 1);
	mlx->ray.draw_end = (mlx->ray.line_height >> 1) + (h >> 1);
	if (mlx->ray.draw_end >= h)
		mlx->ray.draw_end = h;
	i = 0;
	mlx->screen.i -= mlx->screen.h;
	while (i < mlx->ray.draw_start)
		mlx->screen.buffer[mlx->screen.i + i++] = mlx->map.ceil;
	draw_texture(mlx, side);
	i = mlx->ray.draw_end;
	while (i < mlx->screen.h)
		mlx->screen.buffer[mlx->screen.i + i++] = mlx->map.floor;
}
