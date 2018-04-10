/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 08:55:16 by lperret           #+#    #+#             */
/*   Updated: 2016/11/17 22:30:45 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_calcul(int *n, int *length, int *neg)
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
	while (tmp /= 10)
		(*length)++;
}

char			*ft_itoa(int n)
{
	int		length;
	int		neg;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ft_calcul(&n, &length, &neg);
	if (!(str = (char*)malloc(sizeof(*str) * length)))
		return (NULL);
	str[--length] = '\0';
	while (length--)
	{
		str[length] = n % 10 + 48;
		n /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
