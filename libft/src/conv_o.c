/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:46:02 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:46:04 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_conv_o(t_print *elem)
{
	if (elem->plus || elem->space)
		return (0);
	if (elem->minus && elem->zero)
		elem->zero = 0;
	return (1);
}

void		ft_get_hash_o(char *ptr, char *ptr_ptr, t_print *elem)
{
	if (elem->hashtag && elem->char_conv == 'o' && elem->precision == -1)
	{
		if (ptr == ptr_ptr)
			*ptr = '0';
		else
			*(ptr - 1) = '0';
	}
}

static char	*ft_len_alloc(t_print *elem, size_t len)
{
	char	*str;

	str = NULL;
	if (elem->precision > (int)len)
		len = elem->precision;
	if (elem->width > (int)len)
		len = elem->width;
	else if (elem->width <= (int)len && (elem->hashtag))
		len++;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_memset(str, ' ', len);
	return (str);
}

static char	*ft_get_type(char *str, t_print *elem, va_list ap)
{
	intmax_t	nb;

	nb = ft_multicast(ap, elem);
	if (nb == 0 && elem->precision == 0)
	{
		if (!elem->hashtag)
			return (str = ft_strnew(0));
		elem->hashtag = 0;
	}
	elem->hashtag = (nb == 0) ? 0 : elem->hashtag;
	if (elem->type == 'j' || elem->type == 'L' ||
			elem->type == 'l' || elem->type == 'z')
		str = ft_ulotoa_base(nb, 8);
	else if (elem->type == 'H')
		str = ft_uchatoa_base(nb, 8);
	else if (elem->type == 'h')
		str = ft_ushotoa_base(nb, 8);
	else
		str = ft_utoa_base(nb, 8);
	return (str);
}

char		*ft_conv_o(char *str, t_print *elem, va_list ap)
{
	char	*ptr;

	ptr = NULL;
	if (!ft_check_conv_o(elem))
		return (NULL);
	if (!(str = ft_get_type(str, elem, ap)))
		return (NULL);
	ptr = ft_len_alloc(elem, ft_strlen(str));
	ft_set_digit(ptr, str, elem);
	return (ptr);
}
