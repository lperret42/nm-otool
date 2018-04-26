/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_32_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 11:03:05 by lperret           #+#    #+#             */
/*   Updated: 2018/04/26 16:46:28 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint32_t		swap32(uint32_t nb, int to_swap)
{
	uint32_t	i;
	uint32_t	nb_octet;
	uint32_t	ret;

	if (!to_swap)
		return (nb);
	ret = 0;
	nb_octet = sizeof(nb);
	i = 0;
	while (i < nb_octet)
	{
		*((unsigned char *)&ret + i) =
				*((unsigned char *)&nb + (nb_octet - 1 - i));
		i++;
	}
	return (ret);
}

uint64_t		swap64(uint64_t nb, int to_swap)
{
	uint64_t	i;
	uint64_t	nb_octet;
	uint64_t	ret;

	if (!to_swap)
		return (nb);
	ret = 0;
	nb_octet = sizeof(nb);
	i = 0;
	while (i < nb_octet)
	{
		*((unsigned char *)&ret + i) =
				*((unsigned char *)&nb + (nb_octet - 1 - i));
		i++;
	}
	return (ret);
}
