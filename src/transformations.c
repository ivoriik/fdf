/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:23:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/01 16:23:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		vec_multipl(t_mlx *mlx, float m[][4], t_point *p)
{
	int size;

	if (!m)
		return ;
	size = 0;
	while (size < mlx->hei * mlx->wid)
	{
		(*p).nx = m[0][0] * (*p).x + m[0][1] * \
		(*p).y + m[0][2] * (*p).z + m[0][3] * (*p).w;
		mlx->min_x = (!mlx->min_x) ? (*p).nx : fmin((*p).nx, mlx->min_x);
		mlx->max_x = (!mlx->max_x) ? (*p).nx : fmax((*p).nx, mlx->max_x);
		(*p).ny = m[1][0] * (*p).x + m[1][1] * \
		(*p).y + m[1][2] * (*p).z + m[1][3] * (*p).w;
		mlx->min_y = (!mlx->min_y) ? (*p).ny : fmin((*p).ny, mlx->min_y);
		mlx->max_y = (!mlx->max_y) ? (*p).ny : fmax((*p).ny, mlx->max_y);
		(*p).nz = m[2][0] * (*p).x + m[2][1] * \
		(*p).y + m[2][2] * (*p).z + m[2][3] * (*p).w;
		(*p).nw = m[3][0] * (*p).x + m[3][1] * \
		(*p).y + m[3][2] * (*p).z + m[3][3] * (*p).w;
		p++;
		size++;
	}
}

void		vec_multipl2(t_mlx *mlx, float m[][4], t_point *points)
{
	int		size;
	float	x;
	float	y;
	float	z;
	float	w;

	if (!m)
		return ;
	size = -1;
	while (++size < mlx->hei * mlx->wid)
	{
		x = m[0][0] * (*points).nx + m[0][1] * (*points).ny + m[0][2] \
		* (*points).nz + m[0][3] * (*points).nw;
		y = m[1][0] * (*points).nx + m[1][1] * (*points).ny + m[1][2] \
		* (*points).nz + m[1][3] * (*points).nw;
		z = m[2][0] * (*points).nx + m[2][1] * (*points).ny + m[2][2] \
		* (*points).nz + m[2][3] * (*points).nw;
		w = m[3][0] * (*points).nx + m[3][1] * (*points).ny + m[3][2] \
		* (*points).nz + m[3][3] * (*points).nw;
		(*points).nz = z;
		(*points).nw = w;
		(*points).nx = x;
		(*points).ny = y;
		points++;
	}
}

void		set_pos(t_mlx *mlx, t_point *points, t_matrix *res, t_matrix *tmp)
{
	if (!res || !tmp)
		return ;
	if (mlx->min_x < 0)
		mlx->offset_x = (WIDTH - (mlx->max_x - mlx->min_x)) / 2 \
		- mlx->min_x;
	else
		mlx->offset_x = (WIDTH - (mlx->max_x - mlx->min_x)) / 2;
	if (mlx->min_y < 0)
		mlx->offset_y = (HEIGHT - (mlx->max_y - mlx->min_y)) / 2 \
		- mlx->min_y;
	else
		mlx->offset_y = (HEIGHT - (mlx->max_y - mlx->min_y)) / 2;
	res = matrix_move(tmp, mlx->offset_x + mlx->move_x,\
	mlx->offset_y + mlx->move_y, 0.0f);
	vec_multipl2(mlx, res->m, points);
}

static int	alloc_error(t_matrix *m1, t_matrix *m2)
{
	if (m1)
		free(m1);
	if (m2)
		free(m2);
	return (ft_perror("memory allocation failed\n"));
}

int			projection(t_mlx *mlx, t_point *points)
{
	t_matrix	*right;
	t_matrix	*left;
	int			i;

	i = -1;
	right = (t_matrix *)malloc(sizeof(t_matrix));
	left = (t_matrix *)malloc(sizeof(t_matrix));
	if (!left || !right)
		return (alloc_error(right, left));
	matrix_mult(y_rotate(left, mlx->angle_y + mlx->proj_angle_y),\
	x_rotate(right, mlx->angle_x + mlx->proj_angle_x));
	matrix_mult(matrix_scale(right, mlx->scale + mlx->nw_scale), left);
	vec_multipl(mlx, right->m, points);
	set_pos(mlx, points, left, right);
	while (++i < mlx->wid * mlx->hei - 1)
	{
		if (i + mlx->wid < mlx->wid * mlx->hei)
			bresenham(mlx, points[i], points[i + mlx->wid]);
		if (i < (mlx->wid * (i / mlx->wid + 1) - 1))
			bresenham(mlx, points[i], points[i + 1]);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img->ptr, 0, 0);
	free(right);
	free(left);
	return (0);
}
