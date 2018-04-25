/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:07:30 by lperret           #+#    #+#             */
/*   Updated: 2018/04/25 15:24:03 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static uint32_t		swap_uint32(uint32_t nb)
{
	uint32_t	i;
	uint32_t	nb_octet;
	uint32_t	ret;

	ft_printf("begin swap_uint32\n");
	ft_printf("nb: %#x\n", nb);
	ret = 0;
	nb_octet = sizeof(nb);
	i = 0;
	while (i < nb_octet)
	{
		*((unsigned char *)&ret + i) =
				*((unsigned char *)&nb + (nb_octet - 1 - i));
		ft_printf("nb: %#x\n", nb);
		i++;
	}
	ft_printf("end swap_uint32\n");
	return (ret);
}

static int			check_cpu_type(uint32_t cputype_swaped, t_infos infos)
{
	if ((cputype_swaped & CPU_TYPE_X86_64) == CPU_TYPE_X86_64)
		return (0);
	else if (cputype_swaped == CPU_TYPE_I386)
	{
		ft_printf("\n%s (for architecture i386):\n", infos.filename);
		return (0);
	}
	else if (cputype_swaped == CPU_TYPE_POWERPC)
	{
		ft_printf("\n%s (for architecture ppc):\n", infos.filename);
		return (0);
	}
	return (-1);
}

static int			handle_fat_32(struct fat_arch *arch, t_infos infos)
{
	t_infos		new_infos;
	uint32_t	offset_swaped;
	uint32_t	cputype_swaped;

	if (check_addr(NULL, (void*)arch, sizeof(*arch), infos) != 0)
		return (FORMAT_ERROR);
	offset_swaped = swap_uint32(arch->offset);
	cputype_swaped = swap_uint32(arch->cputype);
	//if (cputype_swaped != CPU_TYPE_X86)
	//if ((cputype_swaped & CPU_TYPE_X86_64) != CPU_TYPE_X86_64)
	if (check_cpu_type(cputype_swaped, infos) != 0)
		return (0);
	///*
	ft_printf("arch->offset: %lu\n", arch->offset);
	ft_printf("offset_swaped: %lu\n", offset_swaped);
	ft_printf("swap_uint32(arch->cputype): %u\n", swap_uint32(arch->cputype));
	//*/
	//ft_printf("cputype_swaped: %u\n", cputype_swaped);
	if (check_addr(NULL, (void*)infos.ptr + offset_swaped, 0, infos) != 0)
		return (FORMAT_ERROR);
	ft_memcpy(&new_infos, &infos, sizeof(t_infos));
	new_infos.nbfiles = 0;
	new_infos.filename = NULL;
	//new_infos.ptr = (void*)infos.ptr + offset_swaped;
	new_infos.ptr = infos.ptr + offset_swaped;
	ft_printf("yo1\n");
	ft_printf("new_infos.ptr: %p\n", new_infos.ptr);
	ft_printf("new_infos.ptr: %s\n", new_infos.ptr);
	*(new_infos.ptr) = 5;
	write(1, "hello\n", 6);
	*((uint64_t *)(new_infos.ptr)) = swap_uint32(*((uint32_t *)(new_infos.ptr)));
	ft_printf("yo2\n");
	new_infos.filesize = arch->size;
	new_infos.sec_names = NULL;
	new_infos.syms = NULL;
	//ft_printf("\n%s(%s):\n", infos.filename, (void*)arch + sizeof(*arch));
	//ft_printf("new fat:\n****************************\n");
	//ft_printf("new fat:\n****************************\n");
	return (nm(new_infos));
	//return (handle_32_64(new_infos));
}

int					handle_fats(t_infos infos)
{
	int					error;
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			i;
	uint32_t			n;
	//t_infos				new_infos;

	if (check_addr((void**)&fat, infos.ptr, sizeof(*fat), infos) != 0)
		return (FORMAT_ERROR);
	n = swap_uint32(fat->nfat_arch);
	arch = (void*)infos.ptr + sizeof(*fat);
	i = 0;
	while (i < n)
	{
		error = handle_fat_32(arch, infos);
		if (error != NO_ERROR)
			return (error);
		//if ((swap_uint32(arch->cputype) & CPU_ARCH_ABI64) == CPU_ARCH_ABI64)
		//	break ;
		arch = (void*)arch + sizeof(*arch);
		i++;
	}
	/*
	if (!arch->offset)
		return (0);
	ft_memcpy(&new_infos, &infos, sizeof(t_infos));
	new_infos.ptr = infos.ptr + swap_uint32(arch->offset);
	*/
	return (0);
}
