/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:07:30 by lperret           #+#    #+#             */
/*   Updated: 2018/04/17 15:55:35 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static uint32_t		swap_uint32(uint32_t nb)
{
	uint32_t	i;
	uint32_t	nb_octet;
	uint32_t	ret;

	ret = 0;
	nb_octet = sizeof(nb);
	i = 0;
	while (i < nb_octet)
	{
		*((unsigned char *)&ret + i) =
				*((unsigned char *)&nb + (nb_octet - 1 - i));
		i++;
	}
	return ret;
}

int					handle_fat(char *ptr, char *name, t_options options)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			n;

	fat = (struct fat_header *)ptr;
	n = swap_uint32(fat->nfat_arch);
	arch = (void*)ptr + sizeof(*fat);
	while (n)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			break;
		arch = (void*)arch + sizeof(*arch);
		n--;
	}
	return (nm(ptr + swap_uint32(arch->offset), name, options));
}
