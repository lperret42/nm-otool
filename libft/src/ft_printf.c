/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:47:23 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:47:30 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		len;
	char		*str;
	t_print		*elem;

	len = 0;
	str = NULL;
	if (!(elem = (t_print *)malloc(sizeof(*elem))))
		return (-1);
	elem->len = 0;
	va_start(ap, format);
	if (!(str = ft_root((char *)format, ap, elem)))
		return (-1);
	va_end(ap);
	len = elem->len;
	write(1, str, elem->len);
	free(elem);
	free(str);
	return (len);
}
