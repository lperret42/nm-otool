/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:49:11 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:49:13 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_set_elem(t_print *elem)
{
	elem->hashtag = 0;
	elem->zero = 0;
	elem->minus = 0;
	elem->plus = 0;
	elem->space = 0;
	elem->width = 0;
	elem->precision = 0;
	elem->type = 0;
	elem->char_conv = 0;
	elem->neg = 0;
	elem->putf = 0;
	elem->boolutf = 0;
	elem->next = 0;
	elem->len = 0;
}

static void	ft_parse_format(char *cpy, t_print *elem)
{
	int		i;
	char	*cpy_ptr;

	i = 0;
	cpy_ptr = cpy;
	cpy = ft_parse_flags(cpy, elem);
	cpy = ft_parse_width(cpy, elem);
	cpy = ft_parse_precision(cpy, elem);
	cpy = ft_parse_type(cpy, elem);
	ft_parse_conversion(*cpy, elem);
	while (cpy_ptr[i] != *cpy)
		i++;
	elem->next = i + 1;
}

static char	*ft_conversion(t_print *elem, va_list ap)
{
	int		i;
	char	*str;
	char	*conversion;
	char	*(*table[10])(char*, t_print*, va_list);

	conversion = "csdouxXpb%";
	str = NULL;
	table[0] = &ft_conv_c;
	table[1] = &ft_conv_s;
	table[2] = &ft_conv_d;
	table[3] = &ft_conv_o;
	table[4] = &ft_conv_u;
	table[5] = &ft_conv_x;
	table[6] = &ft_conv_x;
	table[7] = &ft_conv_p;
	table[8] = &ft_conv_b;
	table[9] = &ft_conv_percent;
	i = 0;
	while (conversion[i] != elem->char_conv)
		i++;
	if (!(str = (*table[i])(NULL, elem, ap)))
		str = ft_strdup("(null)");
	if (elem->char_conv != 'c' && elem->char_conv)
		elem->len = ft_strlen(str);
	return (str);
}

static char	*ft_get_full_arg(t_print *elem, char *cpy, va_list ap)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	ft_set_elem(elem);
	ft_parse_format(cpy, elem);
	if (!elem->char_conv)
	{
		if (!*cpy)
		{
			str = ft_strnew(0);
			elem->next = 0;
			return (str);
		}
		str = ft_wild_format(cpy, elem);
		return (str);
	}
	if (!(str = ft_conversion(elem, ap)))
		return (NULL);
	return (str);
}

char		*ft_root(char *format, va_list ap, t_print *elem)
{
	size_t	size;
	char	*str;
	char	*tmp;
	char	*pc;

	str = NULL;
	tmp = NULL;
	size = 0;
	while ((pc = ft_strchr(format, '%')))
	{
		size = elem->len;
		str = ft_strsub(format, 0, pc - format);
		format += (pc - format) + 1;
		pc = ft_get_full_arg(elem, pc + 1, ap);
		str = ft_join_memory_free_all(str, pc, elem);
		format += elem->next;
		if (tmp)
			str = ft_join_memory_free_all_bis(tmp, str, size, elem);
		if (!(tmp = str))
			return (ft_freezer(str));
	}
	if (!str)
		return (ft_cutter(format, elem));
	str = ft_join_memory_free_some(str, format, elem);
	return (str);
}
