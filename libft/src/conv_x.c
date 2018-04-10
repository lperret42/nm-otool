/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:48:42 by lperret           #+#    #+#             */
/*   Updated: 2018/04/09 11:47:26 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_conv_x(t_print *elem)
{
	if (elem->plus || elem->space)
		return (0);
	if (elem->minus && elem->zero)
		elem->zero = 0;
	return (1);
}

void		ft_get_hash_x(char *ptr, char *ptr_ptr, t_print *elem)
{
	if (elem->hashtag && (elem->char_conv == 'x' || elem->char_conv == 'X'))
	{
		if (ptr == ptr_ptr)
		{
			*(ptr) = '0';
			*(ptr + 1) = 'x';
		}
		else
		{
			*(ptr - 2) = '0';
			*(ptr - 1) = 'x';
		}
	}
}

static char	*ft_len_alloc(t_print *elem, size_t len)
{
	char	*str;

	str = NULL;
	if (elem->precision > (int)len)
		len = elem->precision;
	if (elem->width > (int)len && !elem->hashtag)
		len = elem->width;
	if (elem->width > (int)len + 1 && elem->hashtag)
		len = elem->width;
	else if (elem->width == (int)len + 1 && (elem->hashtag))
		len = elem->width + 1;
	else if (elem->width <= (int)len && (elem->hashtag))
		len += 2;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_memset(str, ' ', len);
	return (str);
}

static char	*ft_get_type(char *str, t_print *elem, va_list ap)
{
	intmax_t	nb;

	nb = ft_multicast(ap, elem);
	elem->hashtag = (nb == 0) ? 0 : elem->hashtag;
	if (nb == 0 && elem->precision == 0)
		return (str = ft_strnew(0));
	if (elem->type == 'j' || elem->type == 'L' ||
			elem->type == 'l' || elem->type == 'z')
		str = ft_ulotoa_base(nb, 16);
	else if (elem->type == 'H')
		str = ft_uchatoa_base(nb, 16);
	else if (elem->type == 'h')
		str = ft_ushotoa_base(nb, 16);
	else
		str = ft_utoa_base(nb, 16);
	return (str);
}

char		*ft_conv_x(char *str, t_print *elem, va_list ap)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!ft_check_conv_x(elem))
		return (NULL);
	if (!(str = ft_get_type(str, elem, ap)))
		return (NULL);
	ptr = ft_len_alloc(elem, ft_strlen(str));
	ft_set_digit(ptr, str, elem);
	if (elem->char_conv == 'X')
	{
		while (ptr[i])
		{
			if (ptr[i] != 'x')
				ptr[i] = ft_toupper(ptr[i]);
			i++;
		}
	}
	return (ptr);
}
