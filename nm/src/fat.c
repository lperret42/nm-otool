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

/*
static uint64_t		swap_uint64(uint64_t nb)
{
	uint64_t	i;
	uint64_t	nb_octet;
	uint64_t	ret;

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
*/

int					handle_fat(char *ptr, char *name, t_options options)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			x;
	uint32_t			offset;

	offset = 0;
	if (DEBUG)
	{
		ft_printf("CPU_TYPE_X86_64: %d\n", CPU_TYPE_X86_64);
		ft_printf("sizeof(fat): %d\n", sizeof(fat));
		ft_printf("sizeof(*fat): %d\n", sizeof(*fat));
		ft_printf("sizeof(arch): %d\n", sizeof(arch));
		ft_printf("sizeof(*arch): %d\n", sizeof(*arch));
	}
	//fat = (void*)ptr;
	fat = (struct fat_header *)ptr;
	x = fat->nfat_arch;
	x = swap_uint32(x);
	arch = (void*)ptr + sizeof(*fat);
	while (x)
	{
		if (DEBUG)
		{
			ft_printf("x: %u\n", x);
			ft_printf("arch->cputype: %d\n", arch->cputype);
			ft_printf("arch->cpusubtype: %d\n", arch->cpusubtype);
			ft_printf("swap_uint32(arch->cputype): %d\n", swap_uint32(arch->cputype));
			ft_printf("swap_uint32(arch->cpusubtype): %d\n", swap_uint32(arch->cpusubtype));
			ft_printf("arch->offset: %u\n", arch->offset);
			ft_printf("arch->size: %u\n", arch->size);
			ft_printf("arch->align: %u\n", arch->align);
		}
		//if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
		if (DEBUG)
		{
			ft_printf("swap_uint32(arch->cputype): %u\n", swap_uint32(arch->cputype));
			ft_printf("(cpu_type_t)CPU_TYPE_X86_64: %u\n", (cpu_type_t)CPU_TYPE_X86_64);
			ft_printf("(cpu_type_t)CPU_TYPE_X86: %u\n", (cpu_type_t)CPU_TYPE_X86);
		}
		if (swap_uint32(arch->cputype) == (cpu_type_t)CPU_TYPE_X86_64)
		if (swap_uint32(arch->cputype) == (cpu_type_t)CPU_TYPE_X86_64)
		{
			if (DEBUG)
				ft_printf("CPU_TYPE_X86_64\n");
			offset = arch->offset;
			//break;
		}
		if (DEBUG)
			ft_printf("after offset = arch->offset\n");
		//arch += sizeof(arch) / sizeof(void*);
		arch = (void*)arch + sizeof(*arch);
		//arch = (void*)arch + arch->align;
		x--;
	}
	if (DEBUG)
	{
		ft_printf("offset: %u\n", offset);
		ft_printf("end handle_fat\n");
	}
	if (offset == 0)
		return 0;
	return (nm(ptr + swap_uint32(offset), name, options));
}
