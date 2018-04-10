/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:49:49 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:49:59 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_parse_flags(char *cpy, t_print *elem)
{
	while (*cpy == '#' || *cpy == '0'
			|| *cpy == '-' || *cpy == '+' || *cpy == ' ')
	{
		if (*cpy == '#')
			elem->hashtag = 1;
		else if (*cpy == '0')
			elem->zero = 1;
		else if (*cpy == '-')
			elem->minus = 1;
		else if (*cpy == '+')
			elem->plus = 1;
		else if (*cpy == ' ')
			elem->space = 1;
		cpy++;
	}
	return (cpy);
}

char	*ft_parse_width(char *cpy, t_print *elem)
{
	int		n;

	n = (int)*cpy;
	while (ft_isdigit(n))
	{
		elem->width = elem->width * 10 + (n - '0');
		n = (int)*(++cpy);
	}
	return (cpy);
}

char	*ft_parse_precision(char *cpy, t_print *elem)
{
	int		n;
	int		res;

	n = (int)*cpy;
	res = -1;
	if (n == '.')
	{
		n = (int)*(++cpy);
		res = 0;
		while (ft_isdigit(n))
		{
			res = res * 10 + (n - '0');
			n = (int)*(++cpy);
		}
	}
	elem->precision = res;
	return (cpy);
}

char	*ft_parse_type(char *cpy, t_print *elem)
{
	char	c;

	c = *cpy;
	if (c != 'h' && c != 'l' && c != 'j' && c != 'z')
		return (cpy);
	if (c == 'h' && cpy[1] == 'h')
	{
		elem->type = 'H';
		cpy += 2;
	}
	else if (c == 'l' && cpy[1] == 'l')
	{
		elem->type = 'L';
		cpy += 2;
	}
	else
	{
		elem->type = c;
		cpy += 1;
	}
	return (cpy);
}

int		ft_parse_conversion(char c, t_print *elem)
{
	if (c == 'c' || c == 'C')
		elem->char_conv = 'c';
	else if (c == 's' || c == 'S')
		elem->char_conv = 's';
	else if (c == 'd' || c == 'i' || c == 'D')
		elem->char_conv = 'd';
	else if (c == 'o' || c == 'O')
		elem->char_conv = 'o';
	else if (c == 'u' || c == 'U')
		elem->char_conv = 'u';
	else if (c == 'b' || c == 'B')
		elem->char_conv = 'b';
	else if (c == 'x' || c == 'X' || c == 'p' || c == '%')
		elem->char_conv = c;
	if (c == 'C' || c == 'S' || c == 'D' || c == 'O' || c == 'U')
		elem->type = 'l';
	return (elem->char_conv != 0);
}
