/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 15:03:28 by vbespalk          #+#    #+#             */
/*   Updated: 2018/05/31 15:03:32 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		check_base(char *str, int base)
{
	char	*valid_binary;
	char	*valid_octal;
	char	*valid_decimal;
	char	*valid_hex;
	char	*check_base;

	if (base != 2 && base != 8 && base != 10 && base != 16)
		return (ft_perror("invalid base.\n"));
	valid_binary = "01";
	valid_octal = "01234567";
	valid_decimal = "0123456789";
	valid_hex = "0123456789abcdefxABCDEFX";
	check_base = (base == 2) ? valid_binary : NULL;
	check_base = (base == 8) ? valid_octal : NULL;
	check_base = (base == 10) ? valid_decimal : NULL;
	check_base = (base == 16) ? valid_hex : NULL;
	while (*str)
		if (!ft_strchr(check_base, *str++))
			return (ft_perror("invalid hex value.\n"));
	return (1);
}

int		base_to_decimal(char *s, unsigned int base)
{
	unsigned int num;
	unsigned int len;

	if ((check_base(s, base) == -1))
		return (-1);
	num = 0;
	base = 1;
	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
		s += 2;
	else if (*s == 'x' || *s == 'X')
		s++;
	len = (unsigned int)ft_strlen(s);
	while (len--)
	{
		if (*(s + len) >= '0' && *(s + len) <= '9')
			num += (*(s + len) - '0') * base;
		if (*(s + len) >= 'A' && *(s + len) <= 'F')
			num += (*(s + len) - 55) * base;
		if (*(s + len) >= 'a' && *(s + len) <= 'f')
			num += (*(s + len) - 87) * base;
		if (*(s + len) == 'x')
			ft_perror("invalid hex value.\n");
		base *= 16;
	}
	return (num);
}

void	del_content(void *content, size_t size)
{
	if (size)
		free(content);
	content = NULL;
}

void	ft_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror(NULL);
	exit(-1);
}

int		ft_perror(char *message)
{
	ft_putstr_fd("Error: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror(NULL);
	return (-1);
}
