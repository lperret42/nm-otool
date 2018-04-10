/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_toa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:48:57 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:48:58 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(long long int *nb, int base, t_print *elem)
{
	int				size;
	long long int	tmp;

	size = 0;
	if (*nb < 0)
	{
		if (base == 10)
			elem->neg = 1;
		*nb *= -1;
	}
	tmp = *nb;
	while (tmp /= base)
		size++;
	return (size + 1);
}

char		*ft_slotoa_base(long long int nb, int base, t_print *elem)
{
	int		neg;
	int		size;
	char	*set;
	char	*str;

	neg = 0;
	set = "0123456789abcdef";
	if (base <= 0 || base > 16)
		return (NULL);
	if (nb == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	size = ft_get_size(&nb, base, elem);
	if (!(str = ft_strnew(size)))
		return (NULL);
	while (size--)
	{
		str[size] = set[nb % base];
		nb /= base;
	}
	return (str);
}
