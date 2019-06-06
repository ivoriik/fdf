/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:10:11 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 17:10:16 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 768

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
	float			w;
	float			nx;
	float			ny;
	float			nz;
	float			nw;
	unsigned int	col_pt;
}					t_point;

typedef struct		s_bresenham
{
	t_point			*p0;
	t_point			*p;
	float			nul_p;
	float			dl_x;
	float			dl_y;
	float			error;
	char			axis;
}					t_bresenham;

typedef struct		s_image
{
	void			*ptr;
	char			*data_add;
	int				bpp;
	int				s_line;
	int				endian;
}					t_img;

typedef	struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				wid;
	int				hei;
	float			depth_max;
	float			depth_min;
	int				scale;
	int				nw_scale;
	float			offset_x;
	float			offset_y;
	int				move_x;
	int				move_y;
	float			proj_angle_x;
	float			proj_angle_y;
	float			angle_x;
	float			angle_y;
	float			zero_x;
	float			zero_y;
	float			zero_z;
	float			min_x;
	float			min_y;
	float			max_x;
	float			max_y;
	unsigned int	colors[3];
	char			*str;
	int				legend;
	t_point			*points;
	t_img			*img;
}					t_mlx;

typedef struct		s_matrix
{
	float			m[4][4];
}					t_matrix;

int					init_mlx(t_mlx *mlx, int fd, char **col);
int					bresenham(t_mlx *map, t_point p0, t_point p);
int					hook_keydown(int key, void *param);
unsigned int		get_color(char *line);
int					projection(t_mlx *mlx, t_point *points);
t_matrix			*matrix_scale(t_matrix *m_scale, int scale);
t_matrix			*matrix_move(t_matrix *m_move, int x_m, int y_m, int z_m);
t_matrix			*y_rotate(t_matrix *m_yrot, float angle);
t_matrix			*x_rotate(t_matrix *m_xrot, float angle);
void				izometric_view(t_mlx *mlx);
void				img_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);
void				matrix_mult(t_matrix *right, t_matrix *left);
void				reset(t_mlx *mlx);
void				ortho(t_mlx *mlx);
void				iso(t_mlx *mlx);
void				set_colors(t_mlx *mlx, char *bot, char *mid, char *top);
void				print_legend(t_mlx *mlx);
void				put_legend(t_mlx *mlx);
void				del_content(void *content, size_t size);
void				ft_error(char *message);
int					ft_perror(char *message);
int					check_base(char *str, int base);
int					base_to_decimal(char *str, unsigned int base);
int					read_to_map(int fd, t_mlx **map);
#endif
