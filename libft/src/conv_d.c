/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:44:52 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 12:31:32 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_conv_d(t_print *elem)
{
	if (elem->hashtag)
		return (0);
	if (elem->plus && elem->space)
		elem->space = 0;
	if (elem->minus && elem->zero)
		elem->zero = 0;
	return (1);
}

void		ft_get_plus_d(char *ptr, char *ptr_ptr, t_print *elem)
{
	if (elem->plus && !elem->neg)
	{
		if (ptr == ptr_ptr)
			*ptr = '+';
		else
			*(ptr - 1) = '+';
	}
	if (elem->neg)
	{
		if (ptr == ptr_ptr)
			*ptr = '-';
		else
			*(ptr - 1) = '-';
	}
}

static char	*ft_len_alloc(t_print *elem, size_t len)
{
	char	*str;

	str = NULL;
	if (elem->precision > (int)len)
		len = elem->precision;
	if (elem->neg)
		len++;
	if (elem->width > (int)len)
		len = elem->width;
	else if (elem->width <= (int)len && ((elem->plus || elem->space)
		&& !elem->neg))
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
		return (str = ft_strnew(0));
	else
		return (str = ft_slotoa_base(nb, 10, elem));
}

char		*ft_conv_d(char *str, t_print *elem, va_list ap)
{
	char		*ptr;

	ptr = NULL;
	if (!ft_check_conv_d(elem))
		return (NULL);
	if (!(str = ft_get_type(str, elem, ap)))
		return (NULL);
	ptr = ft_len_alloc(elem, ft_strlen(str));
	ft_set_digit(ptr, str, elem);
	return (ptr);
}
