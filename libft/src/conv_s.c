/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:46:24 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:46:26 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check_conv_s(t_print *elem)
{
	if (elem->hashtag
			|| elem->zero || elem->space || elem->plus
			|| (elem->type && elem->type != 'l'))
		return (0);
	return (1);
}

static char		*ft_set_precision(char *str, size_t len)
{
	char	*ret;

	ret = NULL;
	if (!(ret = ft_strsub(str, 0, len)))
		return (NULL);
	free(str);
	return (ret);
}

static char		*ft_print_null(char *str)
{
	if (!str)
	{
		if (!(str = ft_strdup("(null)")))
			return (NULL);
	}
	else
	{
		if (!(str = ft_strdup(str)))
			return (NULL);
	}
	return (str);
}

static char		*ft_normiblast(char *ptr, char *str, t_print *elem, int len)
{
	if (!elem->boolutf && elem->precision < (int)len && elem->precision != -1)
	{
		len = elem->precision;
		str = ft_set_precision(str, len);
	}
	else if (elem->boolutf && elem->putf < (int)len && elem->precision != -1)
	{
		len = elem->putf;
		str = ft_set_precision(str, len);
	}
	if (elem->width > 0 && elem->minus == 0)
	{
		ptr = ft_set_alpha(elem, len);
		str = ft_join_and_free_all(ptr, str);
	}
	else if (elem->width > 0 && elem->minus == 1)
	{
		ptr = ft_set_alpha(elem, len);
		str = ft_join_and_free_all(str, ptr);
	}
	return (str);
}

char			*ft_conv_s(char *str, t_print *elem, va_list ap)
{
	char	*ptr;
	size_t	len;

	ptr = NULL;
	if (!ft_check_conv_s(elem))
		return (NULL);
	if (elem->type == 'l')
	{
		elem->boolutf = 1;
		if (!(str = ft_conv_sutf(ap, elem)))
			return (NULL);
	}
	else
	{
		str = va_arg(ap, char *);
		if (!(str = ft_print_null(str)))
			return (NULL);
	}
	len = ft_strlen(str);
	str = ft_normiblast(ptr, str, elem, len);
	return (str);
}
