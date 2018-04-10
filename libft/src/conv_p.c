/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:46:12 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:46:15 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_conv_p(t_print *elem)
{
	if (elem->hashtag || elem->plus || elem->space || elem->zero
		|| elem->precision != -1)
		return (0);
	if (elem->type)
		elem->type = 0;
	return (1);
}

void		ft_get_ox(char *ptr, t_print *elem)
{
	if (elem->char_conv == 'p')
	{
		*(ptr - 2) = '0';
		*(ptr - 1) = 'x';
	}
}

static char	*ft_len_alloc(t_print *elem, size_t len)
{
	char	*str;

	str = NULL;
	len += 2;
	if (elem->width > (int)len)
		len = elem->width;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_memset(str, ' ', len);
	return (str);
}

char		*ft_conv_p(char *str, t_print *elem, va_list ap)
{
	char	*ptr;

	ptr = NULL;
	if (!ft_check_conv_p(elem))
		return (NULL);
	if (!(str = ft_ulotoa_base((unsigned long long)va_arg(ap, void *), 16)))
		return (NULL);
	ptr = ft_len_alloc(elem, ft_strlen(str));
	ft_set_digit(ptr, str, elem);
	return (ptr);
}
