/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:44:37 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 12:00:23 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_conv_c(t_print *elem)
{
	if (elem->hashtag || elem->zero || elem->plus
			|| (elem->type && elem->type != 'l'))
		return (0);
	if (elem->space)
		elem->space = 0;
	return (1);
}

static char	*ft_char_zero(char *str, t_print *elem)
{
	char *ret;

	ret = NULL;
	if (elem->width > 1)
		elem->len += elem->width - 1;
	if (!(ret = ft_memalloc(elem->len + 1)))
		return (NULL);
	ft_memset(ret, ' ', elem->len);
	if (elem->minus == 0)
		ret[elem->len - 1] = str[0];
	else
		ret[0] = str[0];
	free(str);
	return (ret);
}

static char	*ft_normiblast(char *ptr, char *str, t_print *elem)
{
	if (str[0] == 0)
		return (ft_char_zero(str, elem));
	if (elem->width > 0 && elem->minus == 0)
	{
		ptr = ft_set_alpha(elem, 1);
		str = ft_join_and_free_all(ptr, str);
	}
	else if (elem->width > 0 && elem->minus == 1)
	{
		ptr = ft_set_alpha(elem, 1);
		str = ft_join_and_free_all(str, ptr);
	}
	elem->len = ft_strlen(str);
	return (str);
}

char		*ft_conv_c(char *str, t_print *elem, va_list ap)
{
	wchar_t		utf;
	char		*ptr;

	ptr = NULL;
	if (!ft_check_conv_c(elem))
		return (NULL);
	if (elem->type == 'l')
	{
		utf = (wchar_t)va_arg(ap, wint_t);
		if (!(str = ft_conv_cutf(utf, elem)))
			return (NULL);
	}
	else
	{
		utf = 0;
		if (!(str = ft_strnew(1)))
			return (NULL);
		elem->len = 1;
		str[0] = (char)va_arg(ap, int);
	}
	str = ft_normiblast(ptr, str, elem);
	return (str);
}
