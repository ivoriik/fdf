/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/19 17:35:55 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	moving(int key, t_mlx *mlx)
{
	if (key == 123)
		mlx->move_x += -10;
	if (key == 124)
		mlx->move_x += 10;
	if (key == 125)
		mlx->move_y += 10;
	if (key == 126)
		mlx->move_y += -10;
}

void	scaling(int key, t_mlx *mlx)
{
	if (key == 69)
		mlx->nw_scale += 2;
	if (key == 78)
	{
		mlx->nw_scale += -2;
		if (mlx->scale + mlx->nw_scale < 0)
			mlx->nw_scale = -mlx->scale;
	}
}

void	rotating(int key, t_mlx *mlx)
{
	if (key == 84)
		mlx->angle_x -= 0.0175;
	if (key == 91)
		mlx->angle_x += 0.0175;
	if (key == 86)
		mlx->angle_y -= 0.0175;
	if (key == 88)
		mlx->angle_y += 0.0175;
}

void	ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img->ptr);
	free(mlx->points);
	free(mlx->img);
	free(mlx);
	exit(0);
}

int		hook_keydown(int key, void *mlx)
{
	if (key == 53)
		ft_exit((t_mlx *)mlx);
	if (key >= 123 && key <= 126)
		moving(key, (t_mlx *)mlx);
	if (key == 69 || key == 78)
		scaling(key, (t_mlx *)mlx);
	if (key == 84 || key == 86 || key == 88 || key == 91)
		rotating(key, (t_mlx *)mlx);
	if (key == 6)
		reset((t_mlx *)mlx);
	if (key == 1)
		iso((t_mlx *)mlx);
	if (key == 0)
		ortho((t_mlx *)mlx);
	if (key == 12)
		put_legend((t_mlx *)mlx);
	ft_bzero(((t_mlx *)mlx)->img->data_add, \
		((t_mlx *)mlx)->img->s_line * HEIGHT);
	projection(((t_mlx *)mlx), ((t_mlx *)mlx)->points);
	if (((t_mlx *)mlx)->legend)
		print_legend(mlx);
	return (0);
}
