/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 17:38:59 by vbespalk          #+#    #+#             */
/*   Updated: 2018/05/05 17:39:01 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zero_axes(t_mlx *mlx, t_point *points)
{
	int size;

	size = 0;
	mlx->zero_x = (mlx->wid - 1) / 2.0f;
	mlx->zero_y = (mlx->hei - 1) / 2.0f;
	mlx->zero_z = (mlx->depth_max + mlx->depth_min) / 2.0f;
	while (size < mlx->hei * mlx->wid)
	{
		(*points).x = (*points).x - mlx->zero_x;
		(*points).y = (*points).y - mlx->zero_y;
		if ((mlx->depth_max - mlx->depth_min))
			(*points).z = (*points).z - mlx->zero_z;
		else
			(*points).z = 0;
		points++;
		size++;
	}
}

int			init_mlx(t_mlx *mlx, int fd, char **col)
{
	ft_bzero(mlx, sizeof(t_mlx));
	if (!(mlx->mlx_ptr = mlx_init()))
		return (ft_perror("connection to the X server failed\n"));
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "FDF")))
		return (ft_perror("impossible to create new window\n"));
	set_colors(mlx, col[0], col[1], col[2]);
	if (!(mlx->img = (t_img *)malloc(sizeof(t_img))))
		return (ft_perror("memory allocation failed\n"));
	if (!(mlx->img->ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT)))
		return (ft_perror("impossible to set up image\n"));
	mlx->img->data_add = mlx_get_data_addr(mlx->img->ptr,\
	&mlx->img->bpp, &mlx->img->s_line, &mlx->img->endian);
	mlx->wid = -1;
	mlx->hei = 0;
	if (read_to_map(fd, &mlx))
		return (-1);
	if (!(mlx->depth_max - mlx->depth_min))
		mlx->scale = (int)sqrt(WIDTH * HEIGHT * 0.25 / (mlx->hei * mlx->wid));
	else
		mlx->scale = (int)sqrt(WIDTH * HEIGHT * 0.25 / \
			(mlx->hei * mlx->wid * (mlx->depth_max - mlx->depth_min) / 2));
	mlx->angle_x = 0.35;
	mlx->angle_y = 0.2625;
	return (0);
}

int			main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;
	char	*col[3];
	int		i;

	ft_bzero(col, sizeof(char *) * 3);
	if ((i = -1) && argc < 2)
		ft_error("usage: fdf file [HEX_COL_BOT] [HEX_COL_MID] [HEX_COL_TOP]\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(NULL);
	if (argc > 2)
		while (++i < 5 && (2 + i) < argc)
			if (base_to_decimal(argv[2 + i], 16) == -1 ||\
			!(col[i] = argv[2 + i]))
				exit(-1);
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))) || init_mlx(mlx, fd, col))
		exit(-1);
	zero_axes(mlx, mlx->points);
	if (projection(mlx, mlx->points))
		exit(-1);
	print_legend(mlx);
	mlx_key_hook(mlx->win_ptr, hook_keydown, (void *)mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
