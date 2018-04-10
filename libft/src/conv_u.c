/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:46:57 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:46:58 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_conv_u(t_print *elem)
{
	if (elem->hashtag || (elem->minus && elem->zero))
		return (0);
	if (elem->plus)
		elem->plus = 0;
	if (elem->space)
		elem->space = 0;
	return (1);
}

static char	*ft_len_alloc(t_print *elem, size_t len)
{
	char	*str;

	str = NULL;
	if (elem->precision > (int)len)
		len = elem->precision;
	if (elem->width > (int)len)
		len = elem->width;
	else if (elem->width <= (int)len && (elem->plus || elem->space))
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
	if (elem->type == 'j' || elem->type == 'L' || elem->type == 'l'
			|| elem->type == 'z')
		str = ft_ulotoa_base(nb, 10);
	else if (elem->type == 'H')
		str = ft_uchatoa_base(nb, 10);
	else if (elem->type == 'h')
		str = ft_ushotoa_base(nb, 10);
	else
		str = ft_utoa_base(nb, 10);
	return (str);
}

char		*ft_conv_u(char *str, t_print *elem, va_list ap)
{
	char	*ptr;

	ptr = NULL;
	if (!ft_check_conv_u(elem))
		return (NULL);
	if (!(str = ft_get_type(str, elem, ap)))
		return (NULL);
	ptr = ft_len_alloc(elem, ft_strlen(str));
	ft_set_digit(ptr, str, elem);
	return (ptr);
}
