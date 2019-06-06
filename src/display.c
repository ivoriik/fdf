/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:45:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 16:45:39 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_legend(t_mlx *mlx)
{
	mlx->legend = 1;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 0, 0, 16774638, \
		"[q] - OFF/ON LEGEND");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 250, 0, 16774638, \
		"[esc] - ESCAPE FDF");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 0, 20, 16774638, \
		"[right/left/up/down arrow] - RIGHT/LEFT/UP/DOWN MOVE");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 0, 40, 16774638, \
		"[6/4/8/2 (Num Lock)] - RIGHT/LEFT/UP/DOWN ROTATION");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 0, 60, 16774638, \
		"[+/- (Num Lock)] - SCALING");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 475, 0, 16774638, \
		"[a] - ORTHOGONAL VIEW");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 725, 0, 16774638, \
		"[s] - ISOMETRICAL VIEW");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 975, 0, 16774638, \
		"[z] - RESET");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 0, 745, 16774638, \
		"NOTE: SPECIFY DESIRABLE COLORS IN ARGUMENTS [BOTTOM], [MIDDLE], \
		[TOP] USING HEX VALUES. DON'T USE 0 FOR BLACK");
}

void	set_colors(t_mlx *mlx, char *bot, char *mid, char *top)
{
	if (!bot || !base_to_decimal(bot, 16))
		mlx->colors[0] = mlx_get_color_value(mlx->mlx_ptr, \
			base_to_decimal("5E3F45", 16));
	else
		mlx->colors[0] = mlx_get_color_value(mlx->mlx_ptr, \
			base_to_decimal(bot, 16));
	if (!mid || !base_to_decimal(mid, 16))
		mlx->colors[1] = mlx_get_color_value(mlx->mlx_ptr, \
			base_to_decimal("3F5E44", 16));
	else
		mlx->colors[1] = mlx_get_color_value(mlx->mlx_ptr, \
			base_to_decimal(mid, 16));
	if (!top || !base_to_decimal(top, 16))
		mlx->colors[2] = mlx_get_color_value(mlx->mlx_ptr, \
			base_to_decimal("C0C9C0", 16));
	else
		mlx->colors[2] = mlx_get_color_value(mlx->mlx_ptr, \
			base_to_decimal(top, 16));
}

void	img_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	t_img	*img;
	char	*data;

	if (!(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT))
		return ;
	img = mlx->img;
	data = img->data_add;
	data += y * img->s_line + img->bpp / 8 * x;
	ft_memcpy(data, &color, sizeof(color));
}

void	put_legend(t_mlx *mlx)
{
	static int on;

	if (!((++on) % 2))
		mlx->legend = 1;
	else
		mlx->legend = 0;
}
