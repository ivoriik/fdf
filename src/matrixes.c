/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 19:50:28 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/03 19:50:30 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*x_rotate(t_matrix *m_xrot, float angle)
{
	if (!m_xrot)
		return (NULL);
	ft_bzero(m_xrot, sizeof(t_matrix));
	m_xrot->m[0][0] = 1.0f;
	m_xrot->m[1][1] = cos(angle);
	m_xrot->m[1][2] = -sin(angle);
	m_xrot->m[2][1] = sin(angle);
	m_xrot->m[2][2] = cos(angle);
	m_xrot->m[3][3] = 1.0f;
	return (m_xrot);
}

t_matrix	*y_rotate(t_matrix *m_yrot, float angle)
{
	if (!m_yrot)
		return (NULL);
	ft_bzero(m_yrot, sizeof(t_matrix));
	m_yrot->m[0][0] = cos(angle);
	m_yrot->m[0][2] = -sin(angle);
	m_yrot->m[1][1] = 1.0f;
	m_yrot->m[2][0] = sin(angle);
	m_yrot->m[2][2] = cos(angle);
	m_yrot->m[3][3] = 1.0f;
	return (m_yrot);
}

t_matrix	*matrix_move(t_matrix *m_move, int x_move, int y_move, int z_move)
{
	if (!m_move)
		return (NULL);
	ft_bzero(m_move, sizeof(t_matrix));
	m_move->m[0][0] = 1.0f;
	m_move->m[1][1] = 1.0f;
	m_move->m[2][2] = 1.0f;
	m_move->m[0][3] += x_move;
	m_move->m[1][3] += y_move;
	m_move->m[2][3] += z_move;
	m_move->m[3][3] = 1.0f;
	return (m_move);
}

t_matrix	*matrix_scale(t_matrix *m_scale, int scale)
{
	if (!m_scale)
		return (NULL);
	ft_bzero(m_scale, sizeof(t_matrix));
	m_scale->m[0][0] = scale * 1.0f;
	m_scale->m[1][1] = scale * 1.0f;
	m_scale->m[2][2] = scale * 1.0f;
	m_scale->m[3][3] = 1.0f;
	return (m_scale);
}

void		matrix_mult(t_matrix *right, t_matrix *left)
{
	float	m[4][4];
	int		i;
	int		j;

	if (!right || !left)
		return ;
	ft_bzero(m, sizeof(m));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = left->m[i][0] * right->m[0][j] + \
			left->m[i][1] * right->m[1][j] + left->m[i][2] \
			* right->m[2][j] + left->m[i][3] * right->m[3][j];
			j++;
		}
		i++;
	}
	ft_memcpy(right->m, m, sizeof(m));
}
