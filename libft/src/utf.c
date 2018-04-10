/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:50:39 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:50:47 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_set_cutf(int byte, wchar_t utf, char *str, t_print *elem)
{
	if (!(str = ft_strnew(byte)))
		return (NULL);
	if (byte == 1)
		str[0] = (unsigned char)utf;
	if (byte == 2)
	{
		str[1] = 0x80 | (utf & 0x3F);
		str[0] = 0xC0 | (utf >> 6 & 0x1F);
	}
	else if (byte == 3)
	{
		str[2] = 0x80 | (utf & 0x3F);
		str[1] = 0x80 | (utf >> 6 & 0x3F);
		str[0] = 0xE0 | (utf >> 12 & 0x0F);
	}
	else if (byte == 4)
	{
		str[3] = 0x80 | (utf & 0x3F);
		str[2] = 0x80 | (utf >> 6 & 0x3F);
		str[1] = 0x80 | (utf >> 12 & 0x3F);
		str[0] = 0xF0 | (utf >> 18 & 0x07);
	}
	elem->len = byte;
	return (str);
}

static void		ft_cut_utf(t_print *elem, wchar_t utf, int tmp)
{
	tmp = elem->putf;
	if (utf >> 7 == 0)
	{
		tmp += 1;
		if (tmp <= elem->precision)
			elem->putf += 1;
	}
	if (utf >> 11 == 0)
	{
		tmp += 2;
		if (tmp <= elem->precision)
			elem->putf += 2;
	}
	if (utf >> 16 == 0)
	{
		tmp += 3;
		if (tmp <= elem->precision)
			elem->putf += 3;
	}
	if (utf >> 21 == 0)
	{
		tmp += 4;
		if (tmp <= elem->precision)
			elem->putf += 4;
	}
}

char			*ft_conv_cutf(wchar_t utf, t_print *elem)
{
	char *str;

	str = NULL;
	if (utf >> 7 == 0)
		str = ft_set_cutf(1, utf, str, elem);
	else if (utf >> 11 == 0)
		str = ft_set_cutf(2, utf, str, elem);
	else if (utf >> 16 == 0)
		str = ft_set_cutf(3, utf, str, elem);
	else if (utf >> 21 == 0)
		str = ft_set_cutf(4, utf, str, elem);
	return (str);
}

char			*ft_conv_sutf(va_list ap, t_print *elem)
{
	char		*str;
	char		*ptr;
	wchar_t		*utf;

	ptr = NULL;
	utf = va_arg(ap, wchar_t *);
	if (!utf)
	{
		if (!(str = ft_strdup("(null)")))
			return (NULL);
		return (str);
	}
	if (!(str = ft_strnew(0)))
		return (NULL);
	while (*utf)
	{
		ft_cut_utf(elem, *utf, 0);
		if (!(ptr = ft_conv_cutf(*utf, elem)))
			return (NULL);
		if (!(str = ft_join_and_free_all(str, ptr)))
			return (NULL);
		utf++;
	}
	return (str);
}
