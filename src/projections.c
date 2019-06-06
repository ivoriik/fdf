/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:42:14 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 14:42:32 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(t_mlx *mlx)
{
	mlx->min_x = 0;
	mlx->max_x = 0;
	mlx->min_y = 0;
	mlx->max_y = 0;
	mlx->angle_x = 0;
	mlx->angle_y = 0;
	izometric_view(mlx);
}

void	ortho(t_mlx *mlx)
{
	mlx->min_x = 0;
	mlx->max_x = 0;
	mlx->min_y = 0;
	mlx->max_y = 0;
	mlx->angle_x = 0;
	mlx->angle_y = 0;
	mlx->proj_angle_x = 0;
	mlx->proj_angle_y = 0;
}

void	reset(t_mlx *mlx)
{
	mlx->min_x = 0;
	mlx->max_x = 0;
	mlx->min_y = 0;
	mlx->max_y = 0;
	mlx->nw_scale = 0;
	mlx->move_x = 0;
	mlx->move_y = 0;
	mlx->angle_x = 0.35;
	mlx->angle_y = 0.2625;
	mlx->proj_angle_x = 0;
	mlx->proj_angle_y = 0;
}

void	izometric_view(t_mlx *mlx)
{
	float rot;
	float new_z;

	rot = sqrt(mlx->zero_x * mlx->zero_x + mlx->points->z * mlx->points->z);
	mlx->proj_angle_y = asin(ft_abs(mlx->zero_x) / rot);
	new_z = sqrt((mlx->wid - 1) * (mlx->wid - 1) + \
		(mlx->hei - 1) * (mlx->hei - 1)) / 2;
	mlx->proj_angle_x = -atan(ft_abs(mlx->zero_y) / new_z);
}
