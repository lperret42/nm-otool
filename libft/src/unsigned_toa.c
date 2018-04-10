/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_toa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:50:15 by lperret           #+#    #+#             */
/*   Updated: 2018/04/06 15:50:17 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ulotoa_base(unsigned long long int nb, int base)
{
	unsigned long long int	tmp;
	int						size;
	char					*set;
	char					*str;

	tmp = nb;
	size = 0;
	set = "0123456789abcdef";
	if (base <= 0 || base > 16)
		return (NULL);
	while (tmp /= base)
		size++;
	if (!(str = ft_strnew(++size)))
		return (NULL);
	while (size--)
	{
		str[size] = set[nb % base];
		nb /= base;
	}
	return (str);
}

char		*ft_utoa_base(unsigned int nb, int base)
{
	unsigned int	tmp;
	int				size;
	char			*set;
	char			*str;

	tmp = nb;
	size = 0;
	set = "0123456789abcdef";
	if (base <= 0 || base > 16)
		return (NULL);
	while (tmp /= base)
		size++;
	if (!(str = ft_strnew(++size)))
		return (NULL);
	while (size--)
	{
		str[size] = set[nb % base];
		nb /= base;
	}
	return (str);
}

char		*ft_ushotoa_base(unsigned short int nb, int base)
{
	unsigned short int	tmp;
	int					size;
	char				*set;
	char				*str;

	tmp = nb;
	size = 0;
	set = "0123456789abcdef";
	if (base <= 0 || base > 16)
		return (NULL);
	while (tmp /= base)
		size++;
	if (!(str = ft_strnew(++size)))
		return (NULL);
	while (size--)
	{
		str[size] = set[nb % base];
		nb /= base;
	}
	return (str);
}

char		*ft_uchatoa_base(unsigned char nb, int base)
{
	unsigned char		tmp;
	int					size;
	char				*set;
	char				*str;

	tmp = nb;
	size = 0;
	set = "0123456789abcdef";
	if (base <= 0 || base > 16)
		return (NULL);
	while (tmp /= base)
		size++;
	if (!(str = ft_strnew(++size)))
		return (NULL);
	while (size--)
	{
		str[size] = set[nb % base];
		nb /= base;
	}
	return (str);
}
