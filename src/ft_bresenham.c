/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:55:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 12:55:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		col(t_mlx *map, t_point p0, t_point p, t_bresenham *br)
{
	float	x0;
	float	range;

	x0 = (br->axis == 'x') ? p0.nx : p0.ny;
	range = fmax(br->dl_x, br->dl_y);
	if (p0.col_pt == p.col_pt)
		return (p0.col_pt);
	else if ((p0.col_pt == map->colors[0] && p.col_pt == map->colors[2])\
	|| (p0.col_pt == map->colors[2] && p.col_pt == map->colors[0]))
	{
		if (x0 < br->nul_p + range / 3)
			return (p0.col_pt);
		else if (x0 < br->nul_p + 2 * (range / 3))
			return (map->colors[1]);
		else
			return (p.col_pt);
	}
	else
		return (x0 < br->nul_p + range / 2) ? (p0.col_pt) : (p.col_pt);
}

void	bresenham_x(t_mlx *map, t_point p0, t_point p, t_bresenham *br)
{
	if (p0.nx > p.nx)
	{
		ft_swap(&(p0.nx), &(p.nx), sizeof(float));
		ft_swap(&(p0.ny), &(p.ny), sizeof(float));
		ft_swap(&(p0.col_pt), &(p.col_pt), sizeof(unsigned int));
	}
	br->nul_p = p0.nx;
	while (p0.nx <= p.nx)
	{
		img_pixel_put(map, p0.nx, p0.ny, col(map, p0, p, br));
		if (br->error < 0)
			br->error = br->error + 2 * br->dl_y;
		else
		{
			(p.ny > p0.ny) ? (p0.ny)++ : (p0.ny)--;
			br->error = br->error + 2 * br->dl_y - 2 * br->dl_x;
		}
		(p0.nx)++;
	}
}

void	bresenham_y(t_mlx *map, t_point p0, t_point p, t_bresenham *br)
{
	if (p0.ny > p.ny)
	{
		ft_swap(&(p0.ny), &(p.ny), sizeof(float));
		ft_swap(&(p0.nx), &(p.nx), sizeof(float));
		ft_swap(&(p0.col_pt), &(p.col_pt), sizeof(unsigned int));
	}
	br->nul_p = p0.ny;
	while (p0.ny <= p.ny)
	{
		img_pixel_put(map, p0.nx, p0.ny, col(map, p0, p, br));
		if (br->error < 0)
			br->error = br->error + 2 * br->dl_x;
		else
		{
			(p.nx > p0.nx) ? (p0.nx)++ : (p0.nx)--;
			br->error = br->error + 2 * br->dl_x - 2 * br->dl_y;
		}
		(p0.ny)++;
	}
}

void	bresenham_xy(t_mlx *map, t_point p0, t_point p, t_bresenham *br)
{
	br->nul_p = p0.nx;
	if (p0.nx > p.nx && p0.ny <= p.ny)
		while (p0.ny <= p.ny)
		{
			img_pixel_put(map, p0.nx, p0.ny, col(map, p0, p, br));
			p0.nx--;
			p0.ny++;
		}
	else if (p0.nx <= p.nx && p0.ny > p.ny)
		while (p0.nx <= p.nx)
		{
			img_pixel_put(map, p0.nx, p0.ny, col(map, p0, p, br));
			(p0.nx)++;
			(p0.ny)--;
		}
	else
		while (p0.nx <= p.nx && p0.ny <= p.ny)
		{
			img_pixel_put(map, p0.nx, p0.ny, col(map, p0, p, br));
			(p0.nx)++;
			(p0.ny)++;
		}
}

int		bresenham(t_mlx *map, t_point p0, t_point p)
{
	t_bresenham br;

	br.dl_x = ft_abs(p.nx - p0.nx);
	br.dl_y = ft_abs(p.ny - p0.ny);
	br.axis = 'x';
	br.error = 2 * br.dl_y - br.dl_x;
	if (ft_abs(p.nx - p0.nx) > ft_abs(p.ny - p0.ny))
		bresenham_x(map, p0, p, &br);
	else if (ft_abs(p.nx - p0.nx) < ft_abs(p.ny - p0.ny))
	{
		br.error = 2 * br.dl_x - br.dl_y;
		br.axis = 'y';
		bresenham_y(map, p0, p, &br);
	}
	else
	{
		if (p0.nx > p.nx && p0.ny > p.ny)
		{
			ft_swap(&(p0.nx), &(p.nx), sizeof(float));
			ft_swap(&(p0.ny), &(p.ny), sizeof(float));
			ft_swap(&(p0.col_pt), &(p.col_pt), sizeof(unsigned int));
		}
		bresenham_xy(map, p0, p, &br);
	}
	return (1);
}
