/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:37:47 by lperret           #+#    #+#             */
/*   Updated: 2017/01/11 18:14:23 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_calcul(int *n, int *length, int *neg, int base)
{
	int		tmp;

	*length = 2;
	*neg = 0;
	tmp = *n;
	if (*n < 0)
	{
		*neg = 1;
		*n = -(*n);
		*length = 3;
	}
	while (tmp /= base)
		(*length)++;
}

char			*ft_itoa_base(int value, int base)
{
	int		length;
	int		neg;
	char	*str;

	if (base <= 0 || base >= 16 || (base != 10 && value < 0))
		return (NULL);
	if (value == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_calcul(&value, &length, &neg, base);
	if (!(str = (char*)malloc(sizeof(*str) * length)))
		return (NULL);
	str[--length] = '\0';
	while (length--)
	{
		if (value % base < 10)
			str[length] = value % base + 48;
		else
			str[length] = value % base + 87;
		value /= base;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
