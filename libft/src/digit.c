/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:49:24 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:49:26 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_filler_starter(int len_d, int len_total, t_print *elem)
{
	int	n;
	int	i;
	int	max;

	n = 0;
	i = len_total - 1;
	max = (elem->precision < len_d) ? len_d : elem->precision;
	if (elem->minus && elem->width > elem->precision && elem->width > len_d)
	{
		n = elem->width - max;
		n = (elem->space || elem->plus ||
				(elem->hashtag && elem->precision == -1
				&& elem->char_conv == 'o')) ? n - 1 : n;
		n = (elem->hashtag && (elem->char_conv == 'x'
					|| elem->char_conv == 'X')) ? n - 2 : n;
		if (elem->char_conv == 'p' && elem->width >= len_total)
			n -= 2;
		else if (elem->char_conv == 'p')
			n -= 1;
		n = (elem->neg) ? n - 1 : n;
		while (n--)
			i--;
	}
	return (i);
}

static char	*ft_get_precision(char *ptr, int len_d, t_print *elem)
{
	char *ret;

	ret = ptr;
	if (elem->precision != -1 && elem->precision > len_d)
	{
		elem->precision -= len_d;
		ptr -= elem->precision;
		ret = ptr;
		while (elem->precision)
		{
			elem->precision--;
			*ptr++ = '0';
		}
	}
	return (ret);
}

static char	*ft_get_zero(char *ptr, int len_d, t_print *elem)
{
	char *ret;

	ret = ptr;
	if (elem->zero && elem->precision == -1 && elem->width > len_d)
	{
		elem->width -= len_d;
		ptr -= elem->width;
		ret = ptr;
		while (elem->width--)
			*ptr++ = '0';
		if (elem->space)
			ret[0] = ' ';
	}
	return (ret);
}

intmax_t	ft_multicast(va_list ap, t_print *elem)
{
	intmax_t	nb;

	if (elem->type == 'j')
		nb = va_arg(ap, intmax_t);
	else if (elem->type == 'L')
		nb = va_arg(ap, long long int);
	else if (elem->type == 'l')
		nb = va_arg(ap, long int);
	else if (elem->type == 'z')
		nb = va_arg(ap, size_t);
	else if (elem->type == 'h')
		nb = (short int)va_arg(ap, int);
	else if (elem->type == 'H')
		nb = (char)va_arg(ap, int);
	else if (elem->type == 'U')
		nb = va_arg(ap, long long int);
	else
		nb = va_arg(ap, int);
	return (nb);
}

void		ft_set_digit(char *ptr, char *str, t_print *elem)
{
	char	*ptr_ptr;
	int		starter;
	int		len_d;
	int		len_total;

	ptr_ptr = ptr;
	len_d = ft_strlen(str);
	len_total = ft_strlen(ptr);
	starter = ft_filler_starter(len_d, len_total, elem);
	ptr = ft_strndcpy(ptr + starter, str);
	ptr = ft_get_precision(ptr, len_d, elem);
	ptr = ft_get_zero(ptr, len_d, elem);
	ft_get_plus_d(ptr, ptr_ptr, elem);
	ft_get_hash_o(ptr, ptr_ptr, elem);
	ft_get_hash_x(ptr, ptr_ptr, elem);
	ft_get_ox(ptr, elem);
}
