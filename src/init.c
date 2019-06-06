/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:44:54 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/28 14:45:07 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		get_col(t_mlx *map, t_point *points)
{
	int		x;
	int		y;
	float	c;

	c = (map->depth_max - map->depth_min) / 3.0f;
	y = 0;
	while (y < map->hei && !(x = 0))
	{
		while (x < map->wid)
		{
			if (!points[y * map->wid + x].col_pt)
			{
				if (points[y * map->wid + x].z <= (c + map->depth_min))
					points[y * map->wid + x].col_pt = map->colors[0];
				else if (points[y * map->wid + x].z <= 2 * c + map->depth_min)
					points[y * map->wid + x].col_pt = map->colors[1];
				else
					points[y * map->wid + x].col_pt = map->colors[2];
			}
			x++;
		}
		y++;
	}
}

static void		get_depth(t_mlx *map, float val)
{
	if (!map->depth_max && !map->depth_min)
	{
		map->depth_max = val;
		map->depth_min = val;
	}
	if (val > map->depth_max)
		map->depth_max = val;
	if (val < map->depth_min)
		map->depth_min = val;
}

static int		get_points(t_mlx *map, t_point *points, char *content, int y)
{
	char	**line;
	int		x;
	int		error;
	char	*str_col;

	x = -1;
	error = 0;
	if (!(line = ft_strsplit(content, ' ')))
		return (ft_perror(NULL));
	while (++x < map->wid)
	{
		(points)[y * map->wid + x] = (t_point) {.x = x, .y = y,\
		.z = ft_atoi(line[x]), .w = 1.0f};
		get_depth(map, (points)[y * map->wid + x].z);
		if (!(str_col = ft_strchr(line[x], ',')) && !ft_isnum(line[x]))
			error = -1;
		if (str_col)
			(points)[y * map->wid + x].col_pt = \
		mlx_get_color_value(map->mlx_ptr, base_to_decimal(++str_col, 16));
		free(line[x]);
	}
	free(line);
	if (error)
		ft_perror("invalid file\n");
	return (error);
}

int				to_points(t_point **points, t_mlx *map, t_list *lst, int y)
{
	if (!(*points = (t_point *)malloc(sizeof(t_point) * map->hei * map->wid)))
		return (ft_perror("memory allocation failed\n"));
	ft_bzero((*points), sizeof(t_point));
	while (++y < map->hei)
	{
		if (get_points(map, *points, (char *)lst->content, y))
			return (-1);
		lst = lst->next;
	}
	get_col(map, *points);
	return (0);
}

int				read_to_map(int fd, t_mlx **map)
{
	t_list	*lst;
	t_list	*new;
	int		error;

	lst = NULL;
	error = 0;
	while (get_next_line(fd, &((*map)->str)) && !error)
	{
		if ((*map)->wid == -1)
			(*map)->wid = (int)ft_nb_words((*map)->str, ' ');
		if ((*map)->wid != (int)ft_nb_words((*map)->str, ' '))
			error = -1;
		if (!(new = ft_lstnew((void *)(*map)->str, ft_strlen((*map)->str))))
		{
			ft_lstdel(&lst, del_content);
			ft_perror(NULL);
		}
		ft_lstaddend(&lst, new);
		++(*map)->hei;
		free((*map)->str);
	}
	if (to_points(&((*map)->points), *map, lst, -1))
		error = -1;
	ft_lstdel(&lst, del_content);
	return (error);
}
